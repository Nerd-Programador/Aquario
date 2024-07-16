#ifndef DS18B20_H
#define DS18B20_H

#include "Oled.h"
#include "DS18b20.h"
#include "Aquecedor.h"
#include "TTP223.h"
#include "Lumen.h"
#include "Logs.h"

/*********************************************************************************************************/

// Definindo os pinos
#define TEMP_DS D2

// Configuração do sensor de temperatura DS18B20
OneWire oneWire(TEMP_DS);
DallasTemperature sensors(&oneWire);

// Variáveis de temperatura
float temperature;
const float TEMP_MIN = 24.0;
const float TEMP_MAX = 28.0;
const float TEMP_TARGET = 26.0;

void setupDS() {
  // Iniciando o sensor DS18B20
  sensors.begin();
}


void loopDS() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // Atualizando o display
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Temperatura: ");
    display.print(temperature);
    display.println(" C");
  }
}

#endif