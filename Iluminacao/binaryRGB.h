#ifndef BINARYRGB_H
#define BINARYRGB_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void binaryRGB() {
  static uint32_t lastChangeTime = 0;  // Armazena o último momento em que a cor foi alterada
  static uint8_t colorIndex = 0;       // Índice da cor atual

  // Definir um array de cores RGB
  uint32_t colors[] = {
    strip.Color(255, 0, 0),    // Vermelho
    strip.Color(0, 255, 0),    // Verde
    strip.Color(0, 0, 255),    // Azul
    strip.Color(255, 255, 0),  // Amarelo
    strip.Color(0, 255, 255),  // Ciano
    strip.Color(255, 0, 255)   // Magenta
  };
  const int numColors = sizeof(colors) / sizeof(colors[0]);  // Número de cores

  // Obter o tempo atual
  uint32_t currentTime = millis();

  // Verificar se passaram 5 segundos (5000 milissegundos) desde a última mudança de cor
  if (currentTime - lastChangeTime >= 5000) {
    // Atualizar o último momento de mudança de cor
    lastChangeTime = currentTime;

    // Avançar para a próxima cor
    colorIndex = (colorIndex + 1) % numColors;
  }

  // Atualizar os LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      // LEDs pares: alternam entre cores RGB
      strip.setPixelColor(i, colors[colorIndex]);
    } else {
      // LEDs ímpares: branco fixo
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
  }

  // Atualizar o strip de LEDs
  strip.show();
}

#endif