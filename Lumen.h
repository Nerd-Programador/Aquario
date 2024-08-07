#ifndef LUMEN_H
#define LUMEN_H

#include <Adafruit_NeoPixel.h>

// Definição dos pinos para LED e botão
#if defined(ESP8266)
  #define LED_PIN D4
  #define BUTTON_PIN D3
#elif defined(ESP32)
  #define LED_PIN 2
  #define BUTTON_PIN 11
#else
  #error "Placa não suportada"
#endif

// Incluir os arquivos de cabeçalho dos efeitos
#include "Iluminacao/binaryLighting.h"
#include "Iluminacao/dayNightCycle.h"
#include "Iluminacao/binaryRGB.h"
#include "Iluminacao/rainbowCycle.h"
#include "Iluminacao/plantGrowth.h"
#include "Iluminacao/sunriseSunset.h"
#include "Iluminacao/stormEffect.h"
#include "Iluminacao/moonlightEffect.h"
#include "Iluminacao/waveEffect.h"
#include "Iluminacao/bubblesEffect.h"
// Inclua outros modos conforme necessário

void binaryLighting();
void dayNightCycle();
void binaryRGB();
void rainbowCycle();
void plantGrowth();
void sunriseSunset();
void stormEffect();
void moonlightEffect();
void waveEffect();
void bubblesEffect();

#define NUM_LEDS 74
#define BRIGHTNESS 255
#define DEBOUNCE_DELAY 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int mode = 0;
unsigned long lastUpdate = 0;
unsigned long modeInterval = 5000;
unsigned long lastDebounceTime = 0;
bool buttonPressed = false;
bool buttonState = false; // Novo estado do botão

void setupLumen() {
  strip.begin();
  strip.show();  // Inicializa todos os LEDs como apagados
  strip.setBrightness(BRIGHTNESS);
  pinMode(BUTTON_PIN, INPUT);
  Serial.println("Lumen inicializado");
}

void desligado() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0); // Define todos os LEDs como apagados
  }
  strip.show();
}

void imprimirNomeModo() {
  switch (mode) {
    case 0:
      Serial.println("Desligado");
      mostrarMensagem("LEDs Desligado");
      break;
    case 1:
      Serial.println("Modo binaryLighting");
      mostrarMensagem("Binary Lighting");
      break;
    case 2:
      Serial.println("Modo dayNightCycle");
      mostrarMensagem("Day Night Cycle");
      break;
    case 3:
      Serial.println("Modo binaryRGB");
      mostrarMensagem("Binary RGB");
      break;
    case 4:
      Serial.println("Modo rainbowCycle");
      mostrarMensagem("Rainbow Cycle");
      break;
    case 5:
      Serial.println("Modo plantGrowth");
      mostrarMensagem("Plant Growth");
      break;
    case 6:
      Serial.println("Modo sunriseSunset");
      mostrarMensagem("Sunrise Sunset");
      break;
    case 7:
      Serial.println("Modo stormEffect");
      mostrarMensagem("Storm Effect");
      break;
    case 8:
      Serial.println("Modo moonlightEffect");
      mostrarMensagem("Moon Light Effect");
      break;
    case 9:
      Serial.println("Modo waveEffect");
      mostrarMensagem("Wave Effect");
      break;
    case 10:
      Serial.println("Modo bubblesEffect");
      mostrarMensagem("Bubbles Effect");
      break;
    default:
      Serial.println("Modo desconhecido: " + String(mode));
      break;
  }
}

void alternarModoLumen() {
  mode++;
  if (mode > 10) { // Ajuste o limite de acordo com o número de modos
    mode = 0;
  }
  imprimirNomeModo();
}

void loopLumen() {
  unsigned long currentTime = millis();
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != buttonState) {
    lastDebounceTime = currentTime;
    buttonState = reading;
  }

  if ((currentTime - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (buttonState == HIGH && !buttonPressed) {
      buttonPressed = true;
      alternarModoLumen();
    } else if (buttonState == LOW) {
      buttonPressed = false;
    }
  }

  switch (mode) {
    case 0:
      desligado();
      break;
    case 1:
      binaryLighting();
      break;
    case 2:
      dayNightCycle();
      break;
    case 3:
      binaryRGB();
      break;
    case 4:
      rainbowCycle();
      break;
    case 5:
      plantGrowth();
      break;
    case 6:
      sunriseSunset();
      break;
    case 7:
      stormEffect();
      break;
    case 8:
      moonlightEffect();
      break;
    case 9:
      waveEffect();
      break;
    case 10:
      bubblesEffect();
      break;
  }

  lastUpdate = currentTime;
}

#endif
