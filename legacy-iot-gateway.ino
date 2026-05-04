/**
 * @file legacy-iot-gateway.ino
 * @author Alvaro Luiz (engcontrol-alv)
 * @brief Phase 1 - Core Network & Captive Portal Provisioning
 * @version 0.1.0
 * @details This module handles the initial Wi-Fi provisioning. 
 * It attempts to connect to a known network; if it fails, it spins up an 
 * Access Point ("ESP01-AP") for configuration. Upon successful connection, 
 * it forces the ESP8266 exclusively into Station (STA) mode, ensuring the 
 * configuration network is closed.
 */

#include <ESP8266WiFi.h>
#include <WiFiManager.h>

void setup() {
  // Initialize UART communication (RX/TX pins) for debugging on the Serial Monitor
  Serial.begin(115200);
  Serial.println("\n--- Legacy-IoT-Gateway | Phase 1 ---");
  Serial.println("Initializing network module...");

  WiFiManager wifiManager;

  // Configuration Phase: Attempt to connect. If it fails, open the Captive Portal (AP)
  if (!wifiManager.autoConnect("ESP01-AP")) {
    Serial.println("Failed to connect. Restarting module...");
    delay(3000);
    ESP.restart();
  }

  // Operation Phase: Disable AP and force Station mode (STA) exclusively
  WiFi.mode(WIFI_STA); 
  
  // Connection established confirmation
  Serial.println("WiFi connection established successfully!");
  Serial.print("Assigned IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Intentionally empty. Wi-Fi keep-alive tasks are handled by the ESP background processes.
}