# Sistema Automatizado de Aquário

![Aquarium Automation](https://th.bing.com/th/id/OIG2.5c7C2Q3iMQ2yC1FinvVe?pid=ImgGn)

Este projeto é um sistema automatizado para controle de aquário usando a plataforma NodeMCU e agora também suportando a placa ESP32. O sistema monitora e controla a temperatura, iluminação e oferece atualizações OTA, além de manter registros de logs.

### Componentes Utilizados

- NodeMCU ou ESP32
- Fita LED WS2812b com 74 LEDs
- Módulo Relé
- Display OLED SSD1306
- Botão Touch TTP223
- Sensor de Temperatura DS18B20
- LDR (não utilizado no código atual)
- FAN PWM (não utilizado no código atual)

### Funcionalidades

#### Monitoramento e Controle de Temperatura

- Utiliza o sensor DS18B20 para medir a temperatura da água.
- Controla um aquecedor através de um relé, mantendo a temperatura da água entre 24°C e 28°C.
- Se a temperatura for inferior a 24°C, o aquecedor é ligado até atingir 26°C.
- Informações de temperatura e estado do aquecedor são exibidas no display OLED.

#### Controle de Iluminação

- Vários modos de iluminação:
  - Iluminação binária (010101...)
  - Simulação de ciclo dia/noite
  - Iluminação binária com LEDs RGB alternando de cor a cada 5000 ms
  - Ciclo de arco-íris suave
  - Outros efeitos como crescimento de plantas, nascer/pôr do sol, efeito de tempestade, luar, ondas e bolhas.
- O botão touch TTP223 controla a iluminação:
  - Toque rápido para ligar/desligar no modo 1
  - Dois toques ou toque longo para alternar entre os modos

#### Atualização OTA

- Permite a atualização do firmware via OTA (Over-the-Air) para NodeMCU e ESP32.
- Exibe o progresso e status da atualização no display OLED.

#### Sistema de Logs

- Registra eventos importantes (inicialização, mudanças de estado, erros) na memória flash.
- Logs podem ser acessados via IP estático configurado.

### Estrutura do Código

O projeto está modularizado nos seguintes arquivos:

- **Aquario.ino**: Arquivo principal que inicializa e executa o loop do sistema.
- **Aquecedor.h**: Controle do aquecedor baseado na temperatura da água.
- **DS18b20.h**: Leitura do sensor de temperatura DS18B20.
- **Logs.h**: Sistema de logs para registro de eventos.
- **Lumen.h**: Controle da iluminação da fita LED WS2812b.
- **OTA.h**: Configuração e manuseio de atualizações OTA.
- **Oled.h**: Controle do display OLED para exibir informações.
- **TTP223.h**: Verificação e controle do botão touch TTP223.

### Bibliotecas Necessárias

Certifique-se de instalar as seguintes bibliotecas no Arduino IDE:

- [Adafruit_NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [OneWire](https://github.com/PaulStoffregen/OneWire)
- [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)
- [WiFi (ESP32)](https://github.com/espressif/arduino-esp32)
- [ESP8266WiFi (NodeMCU)](https://github.com/esp8266/Arduino)
- [ESP8266mDNS (NodeMCU)](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS)
- [WiFiUdp (NodeMCU)](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/src)
- [ArduinoOTA (NodeMCU/ESP32)](https://github.com/esp8266/Arduino/tree/master/libraries/ArduinoOTA)
- [FS (SPIFFS, NodeMCU)](https://github.com/esp8266/Arduino/tree/master/cores/esp8266/spiffs)
- [LittleFS (ESP32)](https://github.com/lorol/LITTLEFS)

### GPIOs Utilizados

#### NodeMCU (ESP8266)

- **D3 (GPIO 0)**: TTP223 Touch Button
- **D4 (GPIO 2)**: WS2812b LED Strip
- **D7 (GPIO 13)**: Relay
- **D6 (GPIO 12)**: FAN PWM
- **D8 (GPIO 15)**: DS18B20

#### ESP32

- **GPIO 11**: TTP223 Touch Button
- **GPIO 2**: WS2812b LED Strip
- **GPIO 13**: Relay
- **GPIO 3**: FAN PWM
- **GPIO 15**: DS18B20

### Instruções de Uso

1. Clone este repositório ou baixe o código-fonte.
2. Abra o arquivo `Aquario.ino` no Arduino IDE.
3. Certifique-se de que todas as bibliotecas necessárias estão instaladas.
4. Configure seu SSID e senha WiFi no arquivo `OTA.h`.
5. Compile e carregue o código para o NodeMCU ou ESP32.
6. Acompanhe o funcionamento pelo display OLED e ajuste conforme necessário.

### Licença

Este projeto é de código aberto e está licenciado sob a [MIT License](LICENSE).

### Contato

Se você tiver dúvidas ou sugestões, sinta-se à vontade para abrir uma issue ou entrar em contato.
