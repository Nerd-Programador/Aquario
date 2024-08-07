#ifndef AQUECEDOR_H
#define AQUECEDOR_H

#include <Arduino.h>
#include "DS18b20.h"
#include "Logs.h"
#include "Oled.h"

// Definições dos pinos para RELAY e FAN
#if defined(ESP8266)
  #define RELAY_PIN D7
  #define FAN_PIN D6
#elif defined(ESP32)
  #define RELAY_PIN 13
  #define FAN_PIN 3
#else
  #error "Placa não suportada"
#endif

// Definições de temperatura
const float TEMP_MIN = 24.0;
const float TEMP_MAX = 28.0;
const float TEMP_TARGET = 26.0;

void setupAquecedor() {
  pinMode(RELAY_PIN, OUTPUT); // Define o pino do relay como saída
  digitalWrite(RELAY_PIN, HIGH); // Inicialmente, relay desligado (se relé de lógica inversa)
  
  pinMode(FAN_PIN, OUTPUT); // Define o pino do fan como saída
  analogWrite(FAN_PIN, 0); // Inicialmente, fan desligado
  
  adicionarLog("Aquecedor e FAN inicializados");
}

void loopAquecedor() {
  float temperature = obterTemperatura(); // Obtém a temperatura atual

  if (temperature == -127.0) {
    // Temperatura inválida detectada
    digitalWrite(RELAY_PIN, HIGH); // Desliga o aquecedor
    adicionarLog("Erro no sensor de temperatura - Aquecedor desligado");
    mostrarMensagem("Erro no sensor!");
    return; // Sai da função para evitar processamento adicional
  }

  // Controle do aquecedor
  if (temperature < TEMP_MIN) {
    digitalWrite(RELAY_PIN, LOW); // Liga o aquecedor (se relé de lógica inversa)
    adicionarLog("Aquecedor ligado - Temp: " + String(temperature) + "C");
  } else if (temperature >= TEMP_TARGET) {
    digitalWrite(RELAY_PIN, HIGH); // Desliga o aquecedor (se relé de lógica inversa)
    adicionarLog("Aquecedor desligado - Temp: " + String(temperature) + "C");
  }

  // Controle do fan
  if (temperature >= TEMP_MAX) {
    analogWrite(FAN_PIN, 255); // Liga o fan na velocidade máxima
    adicionarLog("FAN em velocidade máxima - Temp: " + String(temperature) + "C");
  } else if (temperature >= TEMP_TARGET) {
    analogWrite(FAN_PIN, 128); // Liga o fan na velocidade mínima
    adicionarLog("FAN em velocidade mínima - Temp: " + String(temperature) + "C");
  } else {
    analogWrite(FAN_PIN, 0); // Desliga o fan
    adicionarLog("FAN desligado - Temp: " + String(temperature) + "C");
  }
}

#endif
