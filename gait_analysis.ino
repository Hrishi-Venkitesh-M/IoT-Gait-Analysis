#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Enter_SSID"//SSID of your WiFi network
#define WIFI_PASSWORD "Enter_PASSWORD"//Password of your WiFi network
#define API_KEY "Enter_API_KEY"//Web API Key in the firebase project settings
#define DATABASE_URL "Enter_DATABASE_URL"//Reatime databse URL
#define USER_EMAIL "Enter_EMAIL_ID"//Email you provided for the firebase authentication 
#define USER_PASSWORD "Enter_EMAIL_PASSWORD"//The custom password you made for the above email created for the firebase authentication

#define PIEZO_1_PIN 34
#define PIEZO_2_PIN 35

Adafruit_MPU6050 mpu;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip!");
    while (1);
  }
  Serial.println("MPU6050 initialized!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
}

void loop() {
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 10000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    // Read Piezo sensor values
    int piezo1 = analogRead(PIEZO_1_PIN);
    int piezo2 = analogRead(PIEZO_2_PIN);

    // Read MPU6050 data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Send to Firebase
    Serial.printf("Piezo 1: %s\n", Firebase.RTDB.setInt(&fbdo, "/sensors/piezo1", piezo1) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Piezo 2: %s\n", Firebase.RTDB.setInt(&fbdo, "/sensors/piezo2", piezo2) ? "ok" : fbdo.errorReason().c_str());

    Serial.printf("Accel X: %s\n", Firebase.RTDB.setFloat(&fbdo, "/sensors/accel/x", a.acceleration.x) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Accel Y: %s\n", Firebase.RTDB.setFloat(&fbdo, "/sensors/accel/y", a.acceleration.y) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Accel Z: %s\n", Firebase.RTDB.setFloat(&fbdo, "/sensors/accel/z", a.acceleration.z) ? "ok" : fbdo.errorReason().c_str());

    Serial.printf("Gyro X: %s\n", Firebase.RTDB.setFloat(&fbdo, "/sensors/gyro/x", g.gyro.x) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Gyro Y: %s\n", Firebase.RTDB.setFloat(&fbdo, "/sensors/gyro/y", g.gyro.y) ? "ok" : fbdo.errorReason().c_str());
    Serial.printf("Gyro Z: %s\n", Firebase.RTDB.setFloat(&fbdo, "/sensors/gyro/z", g.gyro.z) ? "ok" : fbdo.errorReason().c_str());

    Serial.println("------------------------------");
  }
}
