#ifndef OTA_H
#define OTA_H

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Placa não suportada"
#endif

#include <ArduinoOTA.h>
#include "Logs.h"

const char* ssid = "Marina";
const char* password = "1Betania2Doidinhos";
const char* hostname = "Aquario";

IPAddress local_IP(192, 168, 15, 90);
IPAddress gateway(192, 168, 15, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns1(8, 8, 8, 8);
IPAddress dns2(8, 8, 4, 4);

void setupWiFi() {
#if defined(ESP8266)
  WiFi.hostname(hostname);
#elif defined(ESP32)
  WiFi.setHostname(hostname);
#endif

  if (!WiFi.config(local_IP, gateway, subnet, dns1, dns2)) {
    adicionarLog("Falha na configuração do IP estático");
  }

  WiFi.begin(ssid, password);
  adicionarLog("Conectando ao Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  adicionarLog("Conectado ao Wi-Fi");
  adicionarLog("Endereço IP: " + WiFi.localIP().toString());
}

void setupOTA() {
  setupWiFi();
  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.setPassword("258096");

  ArduinoOTA.onStart([]() {
    String type = (ArduinoOTA.getCommand() == U_FLASH) ? "Atualização de sketch" : "Atualização do sistema de arquivos";
    adicionarLog("Iniciando OTA: " + type);
  });

  ArduinoOTA.onEnd([]() {
    adicionarLog("OTA concluída");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progresso: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
    String errorMsg = "Erro OTA: ";
    if (error == OTA_AUTH_ERROR) errorMsg += "Falha na autenticação";
    else if (error == OTA_BEGIN_ERROR) errorMsg += "Falha no início";
    else if (error == OTA_CONNECT_ERROR) errorMsg += "Falha na conexão";
    else if (error == OTA_RECEIVE_ERROR) errorMsg += "Falha no recebimento";
    else if (error == OTA_END_ERROR) errorMsg += "Falha no término";
    adicionarLog(errorMsg);
  });

  ArduinoOTA.begin();
  adicionarLog("OTA inicializado");
}

void loopOTA() {
  ArduinoOTA.handle();
}

#endif
