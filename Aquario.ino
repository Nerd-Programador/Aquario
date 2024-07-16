#include "Aquecedor.h"
#include "DS18b20.h"
#include "Logs.h"
#include "Lumen.h"
#include "OTA.h"
#include "Oled.h"
#include "TTP223.h"

void setup() {
  Serial.begin(115200);

  // Inicializar cada módulo
  iniciarOled();
  iniciarDS18b20();
  iniciarAquecedor();
  iniciarLumen();
  iniciarTTP223();
  iniciarOTA();

  // Conectar ao WiFi
  iniciarWiFi("Marina", "1Betania2Doidinhos");
}

void loop() {
  // Atualizações OTA
  atualizarOTA();

  // Controle de temperatura e aquecedor
  controlarAquecedor();

  // Controle de iluminação
  controlarLumen();

  // Atualização do display
  atualizarOled();

  // Verificação do botão touch
  verificarTTP223();
}
