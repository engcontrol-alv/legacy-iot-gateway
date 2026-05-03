# Legacy-IoT-Gateway

**A simple, modular IoT Gateway designed to connect serial-based equipment to modern monitoring systems via MQTT.**

### The Challenge

Many industrial environments rely on reliable but older machines that communicate only through serial interfaces (UART). Integrating these systems into modern networks is often difficult because most commercial solutions are expensive and require proprietary hardware, making small to medium-scale telemetry projects hard to justify.

### The Solution

This project offers a practical gateway built on the **ESP-01 (ESP8266) platform**. It serves as a bridge that reads raw serial data and converts it into **structured JSON messages**. 

The system is designed to work alongside a standard backend (Node-RED, InfluxDB, and MQTT Broker) using **Docker**. This setup provides a professional way to collect and store data using affordable, widely available hardware.

### Key Features

*   **Easy Network Setup (Captive Portal):** Eliminates the need for hardcoded Wi-Fi credentials. If the device cannot connect, it creates a local Wi-Fi network where you can easily enter credentials through a browser.
*   **Data Conversion:** Automatically formats incoming serial strings into JSON packets, making them easy to process in the cloud or local servers.
*   **Ready-to-use Backend:** Includes a Docker Compose file to set up the entire data flow (Broker, Database, and Dashboard) with minimal configuration.

### Architecture

The system is organized into three main layers to ensure modularity:

*   **Field Layer:**  Legacy devices send raw data via Serial to the ESP-01.
*   **Gateway Layer:** The ESP-01 converts raw data into JSON and publishes it to the MQTT Broker via Wi-Fi.
*   **Backend Layer:** Node-RED subscribes to MQTT topics, processes the payload, and stores time-series data in InfluxDB.

### Roadmap & Status

*   [x] **Phase 1:** Basic firmware with Captive Portal for network provisioning.
*   [ ] **Phase 2:** MQTT client implementation and JSON data structuring.
*   [ ] **Phase 3:** Local backend configuration via Docker (Node-RED and InfluxDB).
*   [ ] **Phase 4:** Communication stability tests and latency validation.

