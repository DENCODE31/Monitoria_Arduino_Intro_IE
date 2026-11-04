/*
 * 01_blink.ino - Parpadeo del LED integrado
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: estructura setup()/loop(), pinMode(), digitalWrite(), delay()
 * Montaje: ninguno, el LED "L" ya esta conectado a D13 en la placa
 */

const uint8_t LED_PIN = LED_BUILTIN;   // D13 en el UNO R3
const uint16_t PERIODO_MS = 500;       // 500 ms encendido + 500 ms apagado = 1 Hz

void setup() {
    pinMode(LED_PIN, OUTPUT);          // el pin pasa a ser salida
}

void loop() {
    digitalWrite(LED_PIN, HIGH);       // 5 V -> LED encendido
    delay(PERIODO_MS);
    digitalWrite(LED_PIN, LOW);        // 0 V -> LED apagado
    delay(PERIODO_MS);
}
