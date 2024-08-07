#ifndef DS18B20_H
#define DS18B20_H

#include <OneWire.h>
#include <DallasTemperature.h>

// Definição do pino do sensor DS18B20 para diferentes placas
#if defined(ESP8266)
  #define ONE_WIRE_BUS D8
#elif defined(ESP32)
  #define ONE_WIRE_BUS 15
#else
  #error "Placa não suportada"
#endif

OneWire oneWire(ONE_WIRE_BUS); // Instancia OneWire para comunicação com o sensor
DallasTemperature sensors(&oneWire); // Instancia DallasTemperature com a instância OneWire

// Função para inicializar o sensor DS18B20
void setupDS18b20() {
  sensors.begin();
}

// Função para obter a temperatura em graus Celsius
float obterTemperatura() {
  sensors.requestTemperatures(); // Solicita a temperatura do sensor
  float tempC = sensors.getTempCByIndex(0); // Obtém a temperatura do primeiro sensor encontrado
  return tempC;
}

// Função para obter a temperatura formatada com uma casa decimal
String obterTemperaturaFormatada() {
  float tempC = obterTemperatura();
  return String(tempC, 1); // Formata a temperatura com uma casa decimal
}

#endif
