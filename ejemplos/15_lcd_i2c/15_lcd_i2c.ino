/*
 * 15_lcd_i2c.ino - Pantalla LCD 16x2 con modulo I2C (PCF8574)
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: bus I2C, direcciones de dispositivo, LCD HD44780 en modo 4 bits
 * Conexiones del modulo LCD I2C:
 *   VCC -> 5V
 *   GND -> GND
 *   SDA -> A4
 *   SCL -> A5
 *   Direccion I2C: 0x27 (algunos modulos usan 0x3F)
 *
 * Libreria necesaria: LiquidCrystal_I2C (Programa > Incluir libreria >
 * Administrar librerias > buscar "LiquidCrystal_I2C" > instalar la de
 * John Rickman).
 *
 * Direccion: 0x27 es la comun; algunos modulos vienen en 0x3F.
 * Si no ves texto, ajusta el contraste con el potenciometro del modulo.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t DIR_LCD = 0x27;         // cambia a 0x3F si hace falta
LiquidCrystal_I2C lcd(DIR_LCD, 16, 2);  // direccion, columnas, filas

void setup() {
    Wire.begin();                     // en el UNO, SDA=A4 y SCL=A5

    lcd.init();                       // inicializa el controlador HD44780
    lcd.backlight();                  // enciende la luz de fondo
    lcd.clear();

    lcd.setCursor(0, 0);              // columna 0, fila 0 (fila superior)
    lcd.print("HOLA DESDE UNO");     // <- escribe aqui el mensaje de la fila 0
    lcd.setCursor(0, 1);              // columna 0, fila 1 (fila inferior)
    lcd.print("I2C LCD 16x2");       // <- escribe aqui el mensaje de la fila 1

    Serial.begin(9600);
    Serial.println(F("LCD I2C lista."));
}

void loop() {
    lcd.setCursor(0, 1);
    lcd.print("TIEMPO: ");
    lcd.print(millis() / 1000);       // segundos desde que arranco
    lcd.print(" s   ");               // espacios borran digitos sobrantes

    delay(500);
}
