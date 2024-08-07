#ifndef RAINBOWCOLORS_H
#define RAINBOWCOLORS_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void rainbowCycle() {
  static uint32_t lastUpdate = 0;
  static uint16_t startIndex = 0;

  // Cores do arco-íris
  const uint32_t rainbowColors[] = {
    strip.Color(255, 0, 0),    // Vermelho
    strip.Color(255, 127, 0),  // Laranja
    strip.Color(255, 255, 0),  // Amarelo
    strip.Color(0, 255, 0),    // Verde
    strip.Color(0, 0, 255),    // Azul
    strip.Color(75, 0, 130),   // Índigo
    strip.Color(148, 0, 211)   // Violeta
  };
  const int numColors = sizeof(rainbowColors) / sizeof(rainbowColors[0]);

  // Verificar se passaram 5 segundos (5000 milissegundos) desde a última atualização
  if (millis() - lastUpdate >= 5000) {
    lastUpdate = millis();
    startIndex = (startIndex + 1) % numColors;  // Avançar para a próxima cor
  }

  // Atualizar LEDs para criar um ciclo suave de cores do arco-íris
  for (int i = 0; i < NUM_LEDS; i++) {
    int colorIndex = (startIndex + i) % numColors;
    uint32_t color = rainbowColors[colorIndex];

    // Definir a cor do LED
    strip.setPixelColor(i, color);
  }

  strip.show();
}

#endif