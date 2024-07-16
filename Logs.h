#ifndef LOGS_H
#define LOGS_H

#include <Arduino.h>
#include <FS.h>

String logData = "";

void iniciarLogs() {
  if (!SPIFFS.begin()) {
    Serial.println("Falha ao montar o sistema de arquivos");
    return;
  }
  if (SPIFFS.exists("/logs.txt")) {
    File logFile = SPIFFS.open("/logs.txt", "r");
    if (logFile) {
      while (logFile.available()) {
        logData += logFile.readStringUntil('\n') + "\n";
      }
      logFile.close();
    }
  }
}

void adicionarLog(String mensagem) {
  logData += mensagem + "\n";
  File logFile = SPIFFS.open("/logs.txt", "w");
  if (logFile) {
    logFile.print(logData);
    logFile.close();
  }
}

String obterLogs() {
  return logData;
}

#endif
