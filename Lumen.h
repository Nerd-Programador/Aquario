#ifndef LUMEN_H
#define LUMEN_H

#include <FastLED.h>
#include "Logs.h"

#define LED_PIN     D3
#define NUM_LEDS    50
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
unsigned long previousMillisLED = 0;
const long intervalLED = 5000;
int mode = 0; // Modo de iluminação

void iniciarLumen() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  adicionarLog("Lumen inicializado");
}

void controlarLumen() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisLED >= intervalLED && mode == 3) {
    previousMillisLED = currentMillis;
    rainbowCycle();
  }

  switch (mode) {
    case 0:
      FastLED.clear();
      FastLED.show();
      break;
    case 1:
      binaryLighting();
      break;
    case 2:
      dayNightCycle();
      break;
    case 3:
      binaryRGBLighting();
      break;
    case 4:
      rainbowCycle();
      break;
  }
}

void binaryLighting() {
  for(int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CRGB::White;
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}

void dayNightCycle() {
  unsigned long currentMillis = millis();
  int brightness = (sin(currentMillis / 100000.0 * PI) + 1) * 127;
  fill_solid(leds, NUM_LEDS, CRGB(brightness, brightness, brightness));
  FastLED.show();
}

void binaryRGBLighting() {
  for(int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CHSV((i * 10 + millis() / 100) % 255, 255, 255);
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}

void rainbowCycle() {
  fill_rainbow(leds, NUM_LEDS, millis() / 10, 255 / NUM_LEDS);
  FastLED.show();
}

void alternarModoLumen() {
  mode = (mode + 1) % 5;
  adicionarLog("Modo de iluminação alternado para: " + String(mode));
}

#endif
