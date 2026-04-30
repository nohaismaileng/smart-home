# 🏠 Smart Home Automation System

An embedded system that integrates multiple sensors and actuators to automate home monitoring, safety, and control using Arduino.

---

## 📌 Overview

This project implements a **Smart Home System** capable of detecting environmental changes and automatically reacting using different modules such as:

* Temperature monitoring
* Gas & flame detection
* Motion detection
* Light control
* Door security system

Each function is modular and can operate independently or as part of a complete integrated system.

---

## ⚙️ Features

* 🌡️ Temperature monitoring & fan control
* 🔥 Flame detection with buzzer alert
* 🧪 Gas detection (MQ2 sensor)
* 🚶 Motion detection (PIR sensor)
* 💡 Automatic light control (LDR + relay)
* 🔊 Sound detection system
* 🚪 Door monitoring (reed switch)
* 📏 Distance measurement (ultrasonic sensor)
* 🔒 Smart door lock system
* 🔔 Alarm system using buzzer

---

## 🧠 System Architecture

The system is divided into three main parts:

### 1. Sensors

Collect environmental data:

* Temperature sensor
* Gas sensor (MQ2)
* Flame sensor
* LDR (light sensor)
* PIR motion sensor
* Ultrasonic sensor
* Sound sensor
* Reed switch (door)

---

### 2. Actuators

React based on sensor data:

* Fan (cooling system)
* Buzzer (alarm)
* Relay modules (light / appliances)
* Door lock system

---

### 3. Main Controller

* Arduino processes all inputs
* Executes decision logic
* Controls outputs automatically

---

## 🔌 Hardware Components

* Arduino UNO / Nano
* MQ2 Gas Sensor
* Flame Sensor
* LDR Sensor
* PIR Motion Sensor
* Ultrasonic Sensor (HC-SR04)
* Sound Sensor
* Thermistor / LM35
* Relay Module
* Buzzer
* DC Fan
* Reed Switch
* Electronic Door Lock
* Power Supply

---

## 📂 Project Structure

```id="xj2r2v"
smart-home/
│
├── sensors/
│   ├── temperature/
│   ├── gas/
│   ├── flame/
│   ├── motion/
│   ├── light/
│   ├── sound/
│   ├── ultrasonic/
│   └── door/
│
├── actuators/
│   ├── fan/
│   ├── buzzer/
│   ├── relay/
│   └── lock/
│
├── main/
│   └── main_system.ino
│
├── assets/
│   ├── schematic.png
│   └── pcb_layout.png
│
└── README.md
```

---

## 💻 How It Works

* Sensors continuously collect data
* Arduino analyzes conditions
* System reacts automatically:

  * Turns ON/OFF devices
  * Activates alarms
  * Controls lighting and temperature
  * Secures doors

---

## 🚀 Example Scenarios

* 🔥 Flame detected → Buzzer ON
* 🧪 Gas leak → Alarm ON
* 🌙 Darkness → Light ON automatically
* 🚶 Motion detected → Alert system triggered
* 🌡️ High temperature → Fan ON
* 🚪 Door opened → Security alert

---

## 🧪 Future Improvements

* Add WiFi (ESP32) for remote control
* Mobile app integration
* Cloud data logging
* AI-based decision system
* Voice control (Alexa / Google Assistant)

---

## 👩‍💻 Author

Eng Noha
Embedded Systems & Robotics Engineer

---

## ⭐ Notes

This project demonstrates a **complete embedded smart home system** integrating multiple sensors and automation logic, and can be extended into a full IoT platform.
