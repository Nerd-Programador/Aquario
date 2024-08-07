#ifndef BINARYLIGHTING_H
#define BINARYLIGHTING_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void binaryLighting() {
  static uint32_t lastUpdate = 0;
  static int currentColorIndex = 0;

  const uint32_t rgbColors[] = {
    strip.Color(255, 0, 0),  // Vermelho
    strip.Color(0, 255, 0),  // Verde
    strip.Color(0, 0, 255)   // Azul
  };
  const int numColors = sizeof(rgbColors) / sizeof(rgbColors[0]);

  // Verificar se passaram 5 segundos (5000 milissegundos) desde a última atualização
  if (millis() - lastUpdate >= 5000) {
    lastUpdate = millis();
    currentColorIndex = (currentColorIndex + 1) % numColors;  // Avançar para a próxima cor
  }

  uint32_t currentColor = rgbColors[currentColorIndex];

  // Atualizar LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));  // LEDs ímpares (0-index) brancos
    } else {
      strip.setPixelColor(i, currentColor);  // LEDs pares alternam cores RGB
    }
  }

  strip.show();
}

#endif