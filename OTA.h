#ifndef OTA_H
#define OTA_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "Oled.h"
#include "Logs.h"

void iniciarWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  mostrarMensagem("Connected to WiFi");
  adicionarLog("Conectado ao WiFi");
}

void iniciarOTA() {
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {
      type = "filesystem";
    }
    mostrarMensagem("Start updating " + type);
    adicionarLog("Iniciando atualização OTA: " + type);
  });
  ArduinoOTA.onEnd([]() {
    mostrarMensagem("Update Complete");
    adicionarLog("Atualização OTA concluída");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    mostrarMensagem("Progress: " + String(progress / (total / 100)) + "%");
    adicionarLog("Progresso OTA: " + String(progress / (total / 100)) + "%");
  });
  ArduinoOTA.onError([](ota_error_t error) {
    mostrarMensagem("Error[" + String(error) + "]: " + String(error == OTA_AUTH_ERROR ? "Auth Failed" : 
                      error == OTA_BEGIN_ERROR ? "Begin Failed" : 
                      error == OTA_CONNECT_ERROR ? "Connect Failed" : 
                      error == OTA_RECEIVE_ERROR ? "Receive Failed" : "End Failed"));
    adicionarLog("Erro OTA[" + String(error) + "]: " + String(error == OTA_AUTH_ERROR ? "Auth Failed" : 
                  error == OTA_BEGIN_ERROR ? "Begin Failed" : 
                  error == OTA_CONNECT_ERROR ? "Connect Failed" : 
                  error == OTA_RECEIVE_ERROR ? "Receive Failed" : "End Failed"));
  });
  ArduinoOTA.begin();
}

void atualizarOTA() {
  ArduinoOTA.handle();
}

#endif
