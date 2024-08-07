#ifndef SUNRISESUNSET_H
#define SUNRISESUNSET_H

#include <Adafruit_NeoPixel.h>

extern Adafruit_NeoPixel strip;
#define NUM_LEDS 74

void sunriseSunset() {
  static int brightness = 0;
  static int direction = 1;  // 1 = increasing, -1 = decreasing
  static unsigned long lastChange = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastChange >= 50) {  // Adjust delay for smooth transition
    brightness += direction;
    if (brightness >= 255 || brightness <= 0) {
      direction *= -1;  // Reverse direction at max/min brightness
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(brightness, brightness * 0.8, brightness * 0.6));  // Warm color
    }
    strip.show();
    lastChange = currentTime;
  }
}

#endif