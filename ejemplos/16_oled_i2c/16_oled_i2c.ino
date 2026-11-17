/*
 * 16_oled_i2c.ino - Pantalla OLED SSD1306 128x64 por I2C
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: bus I2C, pantalla de pixeles, buffer de Video, fuentes
 * Conexiones del OLED:
 *   VCC -> 3.3V o 5V segun el regulador del modulo
 *   GND -> GND
 *   SDA -> A4
 *   SCL -> A5
 *   Direccion I2C: 0x3C (algunas pantallas usan 0x3D)
 *
 * Librerias necesarias (Programa > Incluir libreria > Administrar librerias):
 *   - Adafruit GFX Library
 *   - Adafruit SSD1306
 *
 * Direccion: 0x3C es la comun; algunas pantallas usan 0x3D.
 *
 * OJO: hay modulos OLED que solo aceptan 3.3 V. Revisa la etiqueta del
 * regulador antes de conectarlo al pin 5V del UNO.
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const uint8_t ANCHO = 128;            // pixeles horizontales
const uint8_t ALTO  = 64;             // pixeles verticales
const uint8_t DIR_OLED = 0x3C;        // direccion tipica; algunos son 0x3D

// El ultimo parametro es el pin RESET. -1 = no usar pin de reset.
Adafruit_SSD1306 pantalla(ANCHO, ALTO, &Wire, -1);

void setup() {
    Wire.begin();                     // en el UNO, SDA=A4 y SCL=A5

    Serial.begin(9600);

    if (!pantalla.begin(SSD1306_SWITCHCAPVCC, DIR_OLED)) {
        Serial.println(F("No se encontro el OLED. Revisa SDA/SCL y la direccion."));
        while (1);                    // se queda aqui: no tiene sentido seguir
    }

    pantalla.clearDisplay();          // borra el buffer de memoria
    pantalla.setTextSize(1);          // tamano de letra minimo (5x7 pixeles)
    pantalla.setTextColor(SSD1306_WHITE);

    pantalla.setCursor(0, 0);
    pantalla.print(F("HOLA DESDE UNO"));    // <- escribe aqui el mensaje de la linea 1
    pantalla.setCursor(0, 16);
    pantalla.print(F("OLED I2C 128x64"));   // <- escribe aqui el mensaje de la linea 2

    pantalla.display();               // envia el buffer a la pantalla
}

void loop() {
    pantalla.fillRect(0, 40, 128, 9, SSD1306_BLACK);  // limpia solo esa franja

    pantalla.setCursor(0, 40);
    pantalla.print(F("TIEMPO: "));
    pantalla.print(millis() / 1000);
    pantalla.print(F(" s"));

    pantalla.display();               // sin esto no se ve ningun cambio
    delay(500);
}
