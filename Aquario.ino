// Bibliotecas necessárias:
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Arduino.h>

// Chamadas das sketchs
#include "Oled.h"
#include "DS18b20.h"
#include "Aquecedor.h"
#include "TTP223.h"
#include "Lumen.h"
#include "OTA.h"
#include "Logs.h"


void setup() {
  Serial.begin(115200);

  // Inicialização dos módulos
  setupOled();
  setupDS();
  setupRelay();
  setupTTP();
  setupLumen();
  setupOTA();
  setupLogs();
}

void loop() {
  loopOled();
  loopDS();
  loopRelay();
  loopTTP();
  loopLumen();
  loopOTA();
  loopLogs();

}
