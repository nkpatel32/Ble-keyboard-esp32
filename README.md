# 🔐 ESP32 RFID Card Scanner over BLE

This project uses an **ESP32 microcontroller** and an **RFID module** (e.g., MFRC522) to scan RFID cards and transmit their UID data via **BLE (Bluetooth Low Energy)** to a **PC or mobile device**.

> 📡 BLE is used to make the project wireless, allowing it to send card IDs to apps like nRF Connect (mobile) or BLE scanner tools (PC).

---

## 🚀 Features

- 📲 Scans RFID cards and sends UID over BLE
- ⚡ Works with both **PC** and **mobile**
- 🔄 Real-time card detection and response
- ✅ Built with **PlatformIO** and the **Arduino framework**

---

## 🧰 Hardware Requirements

| Component       | Description                     |
|----------------|---------------------------------|
| ESP32 Dev Board| Bluetooth-enabled microcontroller |
| MFRC522 Module | RFID reader (13.56 MHz)         |
| RFID Tags      | 13.56 MHz RFID cards or fobs    |
| Jumper Wires   | For connecting RFID to ESP32     |

---

## 🧪 Wiring (ESP32 ↔ RFID MFRC522)

| MFRC522 Pin | ESP32 Pin  |
|-------------|------------|
| VCC         | 3.3V       |
| GND         | GND        |
| RST         | D22        |
| SDA         | D21        |
| SCK         | D18        |
| MOSI        | D23        |
| MISO        | D19        |


---

## 🛠️ Getting Started

1. **Clone the project**:
   ```bash
   git clone https://github.com/nkpatel32/Ble-keyboard-esp32.git cd esp32-rfid-ble
   cd esp32-rfid-ble


2. Open with VS Code + PlatformIO extension

3.Build and Upload to ESP32:
pio run --target upload

📂 Project Structure
📦 esp32-rfid-ble/
 ┣ 📁 include/
 ┣ 📁 lib/
 ┣ 📁 src/
 ┃ ┗ 📄 main.cpp
 ┣ 📄 platformio.ini
 ┣ 📄 README.md

📎 Dependencies
lib_deps =
  miguelbalboa/MFRC522@^1.4.10
  nimBLE-Arduino


🙌 Credits

Based on the MFRC522 library by Miguel Balboa

BLE stack using NimBLE for ESP32
