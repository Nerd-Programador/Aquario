#ifndef DS18B20_H
#define DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void iniciarDS18b20() {
  sensors.begin();
  adicionarLog("Sensor DS18B20 inicializado");
}

float obterTemperatura() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

#endif
