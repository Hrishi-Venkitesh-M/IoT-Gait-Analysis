# Gait Analysis using ESP32, Piezo Sensors & MPU6050

This project is a simple but powerful experiment in combining hardware and cloud to monitor human gait — a.k.a. how we walk.

Using an ESP32 microcontroller, two piezoelectric pressure sensors, and an MPU6050 accelerometer/gyroscope module, this setup captures both foot pressure and motion data. The collected sensor values are pushed to Firebase Realtime Database in near real-time.

Whether you're into biomechanics, IoT, or just enjoy tinkering with sensors, this one’s for you.

---

## 🔧 What's Inside?

- **ESP32**: The brain of the operation. It handles all sensor readings and talks to Firebase over Wi-Fi.
- **Piezo Discs**: These analog pressure sensors pick up force or vibrations from foot impact.
- **MPU6050**: Provides motion data – acceleration and rotational movement (gyroscope).
- **Firebase Integration**: All the data is streamed to Firebase Realtime Database, making it easy to store, visualize, or analyze later.

---

## 📦 Project Structure

- `gait_analysis.ino` — Main Arduino sketch that reads sensor data and uploads it to Firebase.
- Firebase setup included for:
  - WiFi config
  - API key & DB URL
  - User authentication (email/password)

---

## 🚀 Getting Started

1. Clone this repo or download the code.
2. Open `gait_analysis.ino` in Arduino IDE or PlatformIO.
3. Replace the Firebase config values:
   - `WIFI_SSID`
   - `WIFI_PASSWORD`
   - `API_KEY`
   - `DATABASE_URL`
   - `USER_EMAIL`
   - `USER_PASSWORD`
4. Upload to your ESP32 board.
5. Open Serial Monitor and watch the data stream live. 📊

---

## 📈 Possible Use Cases

- Gait analysis for physical therapy or sports
- Step impact detection for smart insoles
- Movement-based control systems
- Or just geeking out with sensors (no judgment)

---

## 🤝 Contributions

This is a hobby project — feel free to fork it, suggest ideas, or build something cool on top of it.

---

## ☕ Final Words

Thanks for checking out this project! Hope it sparks some inspiration or just helps you learn something new. If you use it for something awesome, I’d love to hear about it.

Happy building! 🛠️
