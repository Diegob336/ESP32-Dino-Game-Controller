# ESP32-Dino-Game-Controller

## Project Overview
This project develops a custom hardware controller for the **Chrome Dino Game** using an **ESP32** microcontroller. The controller uses an **MPU6050** to detect user gestures  and transmits commands to a host PC over a simple, robust **serial protocol**.

It demonstrates:
- **Sensor Integration:** Interfacing with an **MPU6050** to acquire real-time motion data.
- **Gesture Recognition:** Converting raw Gyro readings into **jump/duck** events.
- **Sensor Fusion:** Using the **Madgwick filter** to compute stable orientation (quaternion → pitch/roll) from accel/gyro.
- **Robust Serial Communication:** Framed, checksummed packets for reliable command transfer.
- **Host PC Interaction:** A Python script that receives commands and simulates keystrokes.
- **Modular Design:** Clear separation into drivers, gesture logic, and protocol handling.

---

## Features
- **Microcontroller:** ESP32 (ESP-IDF)
- **Sensor Input:** **MPU6050** (3-axis accel + 3-axis gyro)
- **Gestures:** Jump and Duck
- **UART Protocol:** `[START][CMD][CHK][END]` with checksum
- **PC Controller:** Python script (serial + key simulation)
- **Logging:** `ESP_LOGx` for on-target diagnostics

---

## Hardware Used
- **ESP32 DevKitC** (or compatible ESP32 board)
- **MPU6050** IMU module
- Jumper wires / breadboard as needed


## Software Used
### Embedded Firmware
- **ESP-IDF Toolchain** 
- **FreeRTOS** (bundled with ESP-IDF)
- **Language:** C

### Host PC Script
- **Language:** Python
- **Libraries:** `pyserial` (serial), `keyboard` (key events; Linux may require `/dev/uinput` access)
- **Game:** Chrome Dino (`chrome://dino`)

> **Note (Linux):** If using the `keyboard` library, you may need root or udev rules for `/dev/uinput`.

---

