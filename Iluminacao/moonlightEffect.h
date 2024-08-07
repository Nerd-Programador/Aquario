#ifndef MOONLIGHTEFFECT_H
#define MOONLIGHTEFFECT_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void moonlightEffect() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 50));  // Soft blue light
  }
  strip.show();
}

#endif