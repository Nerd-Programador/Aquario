#ifndef AQUECEDOR_H
#define AQUECEDOR_H

#include "Oled.h"
#include "DS18b20.h"
#include "Aquecedor.h"
#include "TTP223.h"
#include "Lumen.h"
#include "Logs.h"

extern float temperature;
extern const float TEMP_MIN;
extern const float TEMP_MAX;
extern const float TEMP_TARGET;

/*********************************************************************************************************/

// Definindo os pinos
#define RELAY_PIN D1

void setupRelay() {
  // Configurando o pino do relay
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Inicialmente, relay desligado
}

void loopRelay() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Controle do aquecedor
    if (temperature <= TEMP_MIN) {
      digitalWrite(RELAY_PIN, HIGH);  // Liga o aquecedor
    } else if (temperature >= TEMP_TARGET) {
      digitalWrite(RELAY_PIN, LOW);  // Desliga o aquecedor
    }
  }
}

#endif