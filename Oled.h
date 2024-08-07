#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Logs.h"
#include "DS18b20.h" // Para obter a temperatura atual

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaração para um display SSD1306 conectado ao I2C (pinos SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long previousMillis = 0; 
const long interval = 2000; // Intervalo de 2 segundos para alternar informações

bool mostrarAquecedor = true;

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

void setupOled() {
  // Inicializar I2C para ESP8266 ou ESP32
  Wire.begin(-1, -1);

  // Inicializar o display OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Endereço I2C do display OLED
    Serial.println("Falha na alocação do SSD1306");
    adicionarLog("Falha na inicialização do display OLED");
    for (;;); // Não prosseguir, display falhou na inicialização
  }

  display.display();
  delay(2000); // Pequeno delay para o display inicializar
  display.clearDisplay();
  display.display();

  adicionarLog("Display OLED inicializado");
}

void loopOled() {
  display.clearDisplay();

  // Atualizar temperatura da água
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Agua:");
  display.setTextSize(3);
  display.setCursor(0, 17);
  display.print(obterTemperaturaFormatada() + "C");

  // Atualizar informações adicionais com base no tempo
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    mostrarAquecedor = !mostrarAquecedor; // Alterna entre mostrar aquecedor e ventilador
  }

  display.setTextSize(1);
  if (mostrarAquecedor) {
    // Atualizar estado do aquecedor
    display.setCursor(0, 45);
    display.print("Aquecedor: ");
    if (digitalRead(RELAY_PIN) == HIGH) {
      display.println("Desligado");
    } else {
      display.println("Ligado");
    }
  } else {
    // Atualizar estado do ventilador
    display.setCursor(0, 45);
    display.print("FAN: ");
    int fanSpeed = analogRead(FAN_PIN);
    if (fanSpeed == 0) {
      display.println("Desligado");
    } else if (fanSpeed <= 128) {
      display.println("Minima");
    } else {
      display.println("Maxima");
    }
  }

  display.display();
}

void mostrarMensagem(String mensagem) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 55);
  display.println(mensagem);
  display.display();
}

#endif
