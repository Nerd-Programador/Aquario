#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DS18b20.h"
#include "Aquecedor.h"
#include "Logs.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void iniciarOled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();
  adicionarLog("OLED inicializado");
}

void mostrarMensagem(String mensagem) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(mensagem);
  display.display();
}

void atualizarOled() {
  float temperature = obterTemperatura();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.setCursor(0, 10);
  display.print("Aquecedor: ");
  display.print(digitalRead(RELAY_PIN) ? "ON" : "OFF");
  display.setCursor(0, 20);
  display.print("Modo Lumen: ");
  display.print(mode);
  display.display();
}

#endif
