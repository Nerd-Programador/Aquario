#ifndef TTP223_H
#define TTP223_H

#include <Arduino.h>
#include "Lumen.h"
#include "Logs.h"

#define TOUCH_PIN D4
unsigned long touchMillis = 0;
const int debounceDelay = 50;

void iniciarTTP223() {
  pinMode(TOUCH_PIN, INPUT);
  adicionarLog("TTP223 inicializado");
}

void verificarTTP223() {
  static int touchState = LOW;
  int reading = digitalRead(TOUCH_PIN);
  
  if (reading != touchState) {
    touchMillis = millis();
  }

  if ((millis() - touchMillis) > debounceDelay) {
    if (reading == HIGH) {
      alternarModoLumen();
    }
  }
  touchState = reading;
}

#endif
