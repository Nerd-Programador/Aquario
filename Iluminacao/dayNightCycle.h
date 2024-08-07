#ifndef DAYNIGHTCYCLE_H
#define DAYNIGHTCYCLE_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void dayNightCycle() {
  static uint32_t lastUpdate = 0;
  static bool increasing = true;
  static uint8_t brightness = 0;

  const uint32_t cycleDuration = 5000;  // Duração total do ciclo em milissegundos

  // Verificar se passaram 5 segundos (5000 milissegundos) desde a última atualização
  if (millis() - lastUpdate >= (cycleDuration / 255)) {
    lastUpdate = millis();

    // Atualizar brilho
    if (increasing) {
      brightness++;
      if (brightness == 255) {
        increasing = false;
      }
    } else {
      brightness--;
      if (brightness == 0) {
        increasing = true;
      }
    }
  }

  // Atualizar LEDs com o brilho atual
  uint32_t color = strip.Color(brightness, brightness, brightness);
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

#endif