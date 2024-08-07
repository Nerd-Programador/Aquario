#ifndef PLANTGROWTH_H
#define PLANTGROWTH_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void plantGrowth() {
  static uint32_t lastUpdate = 0;
  static bool increasing = true;
  static uint8_t intensity = 0;

  const uint32_t cycleDuration = 600000;  // Duração total do ciclo em milissegundos (10 minutos)

  // Verificar se passou o tempo suficiente para mudar a intensidade
  if (millis() - lastUpdate >= (cycleDuration / 255)) {
    lastUpdate = millis();

    // Atualizar intensidade
    if (increasing) {
      intensity++;
      if (intensity == 255) {
        increasing = false;
      }
    } else {
      intensity--;
      if (intensity == 0) {
        increasing = true;
      }
    }
  }

  // Atualizar LEDs com a intensidade atual
  uint32_t color;
  if (increasing) {
    color = strip.Color(0, 0, intensity);  // Azul crescente
  } else {
    color = strip.Color(intensity, 0, 0);  // Vermelho crescente
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

#endif