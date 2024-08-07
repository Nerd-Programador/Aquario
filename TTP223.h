/*#ifndef TTP223_H
#define TTP223_H

#include "Lumen.h"
#include "Logs.h"

extern void alternarModoLumen();

#if defined(ESP8266)
  #define TTP223_PIN D3
#elif defined(ESP32)
  #define TTP223_PIN 11
#else
  #error "Placa não suportada"
#endif

void setupTTP223() {
  pinMode(TTP223_PIN, INPUT);
  adicionarLog("TTP223 inicializado");
  Serial.println("TTP223 inicializado");
}

void loopTTP223() {
  static unsigned long lastTouchTime = 0;
  static int touchCount = 0;

  if (digitalRead(TTP223_PIN) == HIGH) {
    unsigned long now = millis();
    Serial.println("TTP223 detectou toque");
    if (now - lastTouchTime < 500) {
      touchCount++;
      if (touchCount == 2) {
        Serial.println("Alternando modo Lumen");
        alternarModoLumen();
        touchCount = 0;
      }
    } else {
      touchCount = 1;
    }
    lastTouchTime = now;
  }
}

#endif

*/