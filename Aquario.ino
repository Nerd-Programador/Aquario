#include "Aquecedor.h"
#include "DS18b20.h"
#include "Logs.h"
#include "Lumen.h"
#include "OTA.h"
#include "Oled.h"
#include "TTP223.h"

void setup() {
  Serial.begin(115200); // Iniciar a comunicação serial

  // Inicializar sistema de logs
  setupLogs();

  // Inicializar cada módulo
  setupOled();
  setupDS18b20();
  setupAquecedor();
  setupLumen();
  // setupTTP223(); // Inicialização do sensor touch desativada por enquanto

  // Inicializar OTA (apenas para ESP32 e ESP8266)
  setupOTA();

  adicionarLog("Sistema iniciado");
}

void loop() {
  // Atualizações OTA (apenas para ESP32 e ESP8266)
  loopOTA();

  // Controle de temperatura e aquecedor
  loopAquecedor();

  // Controle de iluminação
  loopLumen();

  // Atualização do display OLED
  loopOled();

  // Verificação do botão touch
  // loopTTP223(); // Loop do sensor touch desativado por enquanto
}
