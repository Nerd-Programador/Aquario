#ifndef OLED_H
#define OLED_H

#include "Oled.h"
#include "DS18b20.h"
#include "Aquecedor.h"
#include "TTP223.h"
#include "Lumen.h"
#include "Logs.h"

extern float temperature;
extern const float TEMP_MIN;
extern const float TEMP_MAX;
extern const float TEMP_TARGET;

/*********************************************************************************************************/

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Inicializando o display OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setupOled() {
  // Iniciando o display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Inicializando...");
  display.display();

  display.clearDisplay();
}


void loopOled() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;



    if (digitalRead(RELAY_PIN) == HIGH) {
      display.println("Heater: ON");
    } else {
      display.println("Heater: OFF");
    }

    display.display();
    delay(2000);
  }
}


#endif