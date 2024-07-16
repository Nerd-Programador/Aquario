#ifndef OTA_H
#define OTA_h

#include "Oled.h"
#include "DS18b20.h"
#include "Aquecedor.h"
#include "TTP223.h"
#include "Lumen.h"
#include "Logs.h"

void setupOTA() {
  // Configurando WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Connected to WiFi");
  display.display();
  
  // Configurando OTA
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Start updating " + type);
    display.display();
  });
  ArduinoOTA.onEnd([]() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Update Complete");
    display.display();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Progress: ");
    display.print(progress / (total / 100));
    display.print("%");
    display.display();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Error[" + String(error) + "]: ");
    if (error == OTA_AUTH_ERROR) {
      display.print("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      display.print("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      display.print("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      display.print("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      display.print("End Failed");
    }
    display.display();
  });
  ArduinoOTA.begin();

}

void loopOTA() {
  ArduinoOTA.handle();

  

}

#endif