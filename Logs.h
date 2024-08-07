#ifndef LOGS_H
#define LOGS_H

#include <Arduino.h>

// Definição do sistema de arquivos para diferentes placas
#if defined(ESP8266)
  #include <FS.h>
  #define FILESYSTEM SPIFFS
#elif defined(ESP32)
  #include <LittleFS.h>
  #define FILESYSTEM LittleFS
#else
  #error "Placa não suportada"
#endif

String logData = ""; // Variável para armazenar logs em memória

// Função para iniciar o sistema de logs
void setupLogs() {
  // Inicializa o sistema de arquivos
  if (!FILESYSTEM.begin()) {
    Serial.println("Falha ao montar o sistema de arquivos");
    return;
  }
  
  // Carrega logs anteriores, se existirem
  if (FILESYSTEM.exists("/logs.txt")) {
    File logFile = FILESYSTEM.open("/logs.txt", "r");
    if (logFile) {
      while (logFile.available()) {
        logData += logFile.readStringUntil('\n') + "\n";
      }
      logFile.close();
    }
  }
}

// Função para adicionar um log
void adicionarLog(String mensagem) {
  logData += mensagem + "\n"; // Adiciona a nova mensagem ao log em memória
  
  // Abre o arquivo de log para escrita e salva os logs em memória no arquivo
  File logFile = FILESYSTEM.open("/logs.txt", "w");
  if (logFile) {
    logFile.print(logData);
    logFile.close();
  }
}

// Função para obter todos os logs como uma string
String obterLogs() {
  return logData;
}

#endif
