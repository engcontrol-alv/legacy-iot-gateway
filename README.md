# Resilient IoT Edge

> **Reference firmware for resilient IoT systems with local persistence in LittleFS and asynchronous synchronization via MQTT.**
> Designed to operate on dual-core hardware (ESP32), aiming to mitigate data loss during severe connectivity failures.

![Status](https://img.shields.io/badge/Status-Active%20Development-success)
![Hardware](https://img.shields.io/badge/Hardware-ESP32--S3-orange)
![RTOS](https://img.shields.io/badge/OS-FreeRTOS-green)
![CI/CD](https://img.shields.io/badge/Build-Passing-brightgreen)

## Overview
This project implements an Edge Computing architecture focused on uninterrupted telemetry. This firmware utilizes true parallelism: Core 0 collects real-time sensor data, while Core 1 manages the TCP/IP stack. 

In the event of Wi-Fi network or MQTT Broker unavailability, the data flow is automatically redirected to a non-volatile circular buffer in Flash memory. Upon reestablishing the connection, the system performs Store-and-Forward, synchronizing the delayed data transparently and autonomously.

## Main Features
* **Multithreading (Dual-Core):** Isolated tasks via FreeRTOS.
* **Persistence in LittleFS:** Lightweight and corruption-resistant file system (Wear Leveling).
* **MQTT Auto-Recovery:** Timeout detection algorithm (Keep-Alive) and state transition without manual intervention.
* **Local Diagnostics:** Real-time status interface via integrated OLED display.

## Technology Stack & Hardware
* **Microcontroller:** Heltec WiFi LoRa 32 V3 (ESP32-S3FN8 Dual-Core Xtensa LX7)
* **Framework:** C++ / Arduino Core for ESP32 running on FreeRTOS
* **Environment:** PlatformIO
* **Protocols:** Wi-Fi 802.11 b/g/n, MQTT 5.0 (QoS 1)

### Hardware Notes (Heltec V3)
The following pinout configurations were used for this board:
* **OLED Display Pinout:** `SDA: 17`, `SCL: 18`, `RST: 21`, `Vext (Power): 36` (Active LOW).
* **Serial Monitor (USB CDC):** Due to the use of the native ESP32-S3 USB port, the *build_flags* `-D ARDUINO_USB_MODE=1` and `-D ARDUINO_USB_CDC_ON_BOOT=1` are mandatory to prevent boot crashes.

## Repository Structure
```text
resilient-iot-edge/
├── docs/
│   ├── architecture/      # State diagrams and design documentation
│   └── tests/             # QA: Test Cases and Validation Plan (IEEE 829)
├── firmware/              # ESP32 source code (PlatformIO)
│   ├── include/           # Headers (.h)
│   └── src/               # Main logic (.cpp)
├── scripts/               # Auxiliary tools for log collection
└── .github/workflows/     # CI/CD: Build automation
```

Development Status
[x] Phase 0 (Setup & Planning): Repository structuring, architecture definition, and test plan creation.

[x] Phase 0.5 (Hardware & RTOS Base): Pinout validation (Heltec V3), USB Serial stabilization, and Multi-Core skeleton implementation (FreeRTOS).

[ ] Phase 1 (Local Storage): LittleFS configuration and circular buffer implementation (Core 0).

[ ] Phase 2 (Connectivity): Wi-Fi/MQTT integration and network failure detection routine (Core 1).

[ ] Phase 3 (Synchronization): Store-and-Forward logic development for sending backlogged data post-failure.

[ ] Phase 4 (Final Validation): Practical tests simulating network blackouts and integration with orchestrator (Node-RED).