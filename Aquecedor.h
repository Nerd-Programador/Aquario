#ifndef AQUECEDOR_H
#define AQUECEDOR_H

#include <Arduino.h>
#include "DS18b20.h"
#include "Logs.h"

#define RELAY_PIN D1
const float TEMP_MIN = 24.0;
const float TEMP_MAX = 28.0;
const float TEMP_TARGET = 26.0;

void iniciarAquecedor() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Inicialmente, relay desligado
  adicionarLog("Aquecedor inicializado");
}

void controlarAquecedor() {
  float temperature = obterTemperatura();

  if (temperature <= TEMP_MIN) {
    digitalWrite(RELAY_PIN, HIGH); // Liga o aquecedor
    adicionarLog("Aquecedor ligado - Temp: " + String(temperature) + "C");
  } else if (temperature >= TEMP_TARGET) {
    digitalWrite(RELAY_PIN, LOW); // Desliga o aquecedor
    adicionarLog("Aquecedor desligado - Temp: " + String(temperature) + "C");
  }
}

#endif
