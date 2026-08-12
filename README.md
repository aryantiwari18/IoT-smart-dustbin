# IoT-Based Smart Dustbin with SMS Alert and GPS

An IoT-based smart dustbin that monitors the garbage level using an ultrasonic sensor and sends an SMS alert with the dustbin's GPS location when it becomes full.

## 📌 Project Overview

Traditional dustbins require manual checking to determine whether they are full. This project automates that process by using an ultrasonic sensor to measure the available space inside the dustbin.

When the garbage reaches the defined full level, the Arduino checks the GPS location and uses a GSM module to send an SMS alert containing a Google Maps location link.

## ✨ Features

- Automatic garbage-level detection
- Ultrasonic distance measurement
- SMS alert when the dustbin becomes full
- GPS location tracking
- Google Maps location link in the SMS
- Automatic reset after the dustbin is emptied
- Arduino-based embedded system

## 🧰 Components Required

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno | 1 | Main controller |
| HC-SR04 Ultrasonic Sensor | 1 | Measures garbage level |
| SIM800L GSM Module | 1 | Sends SMS |
| NEO-6M GPS Module | 1 | Provides location |
| Smart Dustbin | 1 | Waste container |
| Jumper Wires | As required | Connections |
| Suitable Power Supply | 1 | Powers the circuit |

## 🔌 Pin Connections

### HC-SR04

| HC-SR04 | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | D9 |
| ECHO | D10 |

### SIM800L

| SIM800L | Arduino |
|---|---|
| TX | D7 |
| RX | D8 |
| GND | GND |
| VCC | Use a suitable stable supply according to the SIM800L board requirements |

### NEO-6M GPS

| NEO-6M | Arduino |
|---|---|
| TX | D4 |
| RX | D3 |
| GND | GND |
| VCC | According to the GPS module specification |

> **Important:** SIM800L modules can require a separate, stable power supply with sufficient current. Do not power a bare SIM800L directly from an Arduino Uno 5V pin unless your specific board explicitly supports it.



## ⚙️ Working Principle

1. The HC-SR04 sends an ultrasonic pulse into the dustbin.
2. The echo time is converted into distance in centimeters.
3. The Arduino compares the measured distance with the configured full-level threshold.
4. When the distance is **5 cm or less**, the dustbin is considered full.
5. The NEO-6M provides the latitude and longitude.
6. The SIM800L sends an SMS to the configured phone number.
7. The SMS contains a Google Maps URL generated from the GPS coordinates.
8. Once the dustbin is emptied, the alert state resets and another alert can be sent the next time it becomes full.

## 📏 Current Configuration

The code is configured for:

- Dustbin height: **30 cm**
- Full threshold: **5 cm**
- Ultrasonic TRIG: **D9**
- Ultrasonic ECHO: **D10**
- SIM800L SoftwareSerial: **D7, D8**
- GPS SoftwareSerial: **D4, D3**
- Serial baud rate: **9600**

You can change these values at the top of `smart_dustbin.ino`.

## 📱 SMS Example

When the dustbin is full, the system sends an SMS similar to:

```text
ALERT: Smart Dustbin is FULL!
Location: https://maps.google.com/?q=21.1458,79.0882
```

The coordinates will be generated from the GPS module.

## 💻 Software Requirements

- Arduino IDE
- Arduino Uno board package
- `TinyGPS++` library
- `SoftwareSerial` library

### Installing TinyGPS++

In Arduino IDE:

**Sketch → Include Library → Manage Libraries**

Search for:

`TinyGPSPlus`

Install the library by **Mikal Hart**.

`SoftwareSerial` is normally included with the Arduino AVR core.

## 🚀 Upload Instructions

1. Open `smart_dustbin.ino` in Arduino IDE.
2. Install the required libraries.
3. Select **Arduino Uno** under **Tools → Board**.
4. Select the correct COM/serial port.
5. Replace `+91XXXXXXXXXX` in the code with the alert recipient's phone number.
6. Connect the modules according to the pin table.
7. Power the modules with suitable supplies.
8. Upload the code.
9. Open Serial Monitor at **9600 baud**.
10. Wait for the GPS to obtain a valid location.
11. Place enough material inside the dustbin to reach the configured full threshold.
12. Check the SMS alert.

## 📂 Repository Structure

```text
iot-smart-dustbin/
│
├── smart_dustbin.ino
└── README.md
```

## 📊 Expected Output

Serial Monitor:

```text
IoT Smart Dustbin Started
Distance from sensor: 18 cm
Distance from sensor: 10 cm
Distance from sensor: 5 cm
Dustbin FULL!
Latitude: XX.XXXXXX
Longitude: XX.XXXXXX
SMS sent.
```

## ⚠️ Important Notes

- GPS may take some time to obtain a satellite fix, especially indoors.
- The SIM800L requires a compatible SIM card and cellular network.
- Use a stable power supply for the GSM module.
- Keep the GPS antenna in a position where it can receive satellite signals.
- Test the ultrasonic sensor before installing it permanently.
- The full threshold should be adjusted according to the actual dustbin dimensions.
- Replace the placeholder phone number before testing SMS functionality.

## 🔮 Future Scope

The project can be expanded with:

- Multiple smart dustbins connected to a cloud dashboard
- Wi-Fi/LoRa/4G connectivity
- Real-time web or mobile monitoring
- Automatic collection-route optimization
- Waste classification using sensors or AI
- Solar-powered operation
- Battery monitoring
- Cloud-based data storage and analytics

## 🎯 Applications

- Smart cities
- Public parks
- Schools and colleges
- Hospitals
- Offices
- Railway stations
- Bus stations
- Residential societies
- Municipal waste-management systems

## 👨‍💻 Author

**Aryan Tiwari**

Information Technology Engineering Student

## 📄 License

This project is intended for educational and academic purposes.

