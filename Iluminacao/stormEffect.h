#ifndef STORMEFFECT_H
#define STORMEFFECT_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void stormEffect() {
  static bool lightning = false;
  static unsigned long lastChange = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastChange >= random(50, 500)) {  // Random lightning intervals
    lightning = !lightning;
    uint32_t color = lightning ? strip.Color(255, 255, 255) : strip.Color(0, 0, 0);  // Lightning flash
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    lastChange = currentTime;
  }
}

#endif