#ifndef BUBBLESEFFECT_H
#define BUBBLESEFFECT_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void bubblesEffect() {
  static int position = 0;
  strip.clear();
  for (int i = position; i < NUM_LEDS; i += 10) {
    strip.setPixelColor(i, strip.Color(0, 100, 255));  // Blueish bubble color
  }
  strip.show();
  position++;
  if (position >= 10) position = 0;
  delay(100);
}

#endif