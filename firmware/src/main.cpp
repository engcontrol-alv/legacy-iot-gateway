#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ── Heltec WiFi LoRa 32 V3 (ESP32-S3) — correct pinout ──────────────────────
#define VEXT_PIN     36   // External display power (LOW = on)
#define OLED_RST_PIN 21   // SSD1306 Reset (active LOW)
#define OLED_SDA     17   // I²C Data
#define OLED_SCL     18   // I²C Clock

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64

// Passes OLED_RST_PIN to the constructor → the library manages the reset on its own
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\n── Heltec V3 init ──");

  // 1. Turn on Vext (powers the OLED module)
  Serial.println("1. Vext ON  →  GPIO 36 LOW");
  pinMode(VEXT_PIN, OUTPUT);
  digitalWrite(VEXT_PIN, LOW);
  delay(200);

  // 2. I²C with SDA/SCL in the correct order
  Serial.println("2. Wire.begin(SDA=17, SCL=18)");
  Wire.begin(OLED_SDA, OLED_SCL);

  // 3. Initialize the display
  //    The library pulses GPIO 21 (LOW→HIGH) automatically via constructor
  Serial.println("3. display.begin()");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("   ERROR: SSD1306 did not respond. Check I²C.");
    for (;;);
  }
  Serial.println("   OK.");

  // 4. Render — without this block, the buffer stays black
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Heltec V3");

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Display OK!");
  display.println("SDA:17 SCL:18");
  display.println("RST:21 Vext:36");

  display.display();   // ← sends the buffer to the physical panel
  Serial.println("Display ready.");
}

void loop() {
  // Blinks a status line to confirm the loop is running
  static uint32_t t = 0;
  static uint8_t  tick = 0;
  if (millis() - t > 1000) {
    t = millis();
    display.fillRect(0, 48, SCREEN_WIDTH, 16, SSD1306_BLACK);
    display.setCursor(0, 52);
    display.setTextSize(1);
    display.printf("Up: %lus  t:%u", millis() / 1000, tick++);
    display.display();
  }
}