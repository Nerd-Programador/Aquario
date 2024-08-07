#ifndef WAVEEFFECT_H
#define WAVEEFFECT_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void waveEffect() {
  static uint16_t j = 0;
  for (int i = 0; i < strip.numPixels(); i++) {
    uint8_t wave = (sin((i + j) * 0.1) * 127) + 128;  // Create wave pattern
    strip.setPixelColor(i, strip.Color(0, 0, wave));  // Blue wave
  }
  strip.show();
  j++;
  delay(20);
}

#endif