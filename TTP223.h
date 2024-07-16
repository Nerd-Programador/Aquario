#ifndef TTP223_H
#define TTP223_h

#include "Oled.h"
#include "DS18b20.h"
#include "Aquecedor.h"
#include "Lumen.h"
#include "Logs.h"

/*********************************************************************************************************/

void setupTTP() {
}

void loopTTP() {
  // Alternar modos de iluminação
  if (digitalRead(TOUCH_PIN) == HIGH) {
    delay(50);  // Debounce
    if (digitalRead(TOUCH_PIN) == HIGH) {
      mode = (mode + 1) % 5;  // Alterna entre os modos 0 a 4 (modo 0 é apagado)
      delay(300);             // Para evitar múltiplas detecções
    }
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

#endif