/*
 * 02_semaforo_peatonal.ino - Semaforo de tres estados
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: varias salidas digitales, secuencia temporizada, funciones propias
 * Montaje: LED rojo en D8, amarillo en D9, verde en D10 (220 ohm cada uno)
 */

const uint8_t LED_ROJO     = 8;
const uint8_t LED_AMARILLO = 9;
const uint8_t LED_VERDE    = 10;

const uint16_t T_VERDE    = 4000;   // tiempo en verde
const uint16_t T_AMARILLO = 1000;   // tiempo en amarillo
const uint16_t T_ROJO     = 4000;   // tiempo en rojo

void apagarTodos() {
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_VERDE, LOW);
}

void setup() {
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_AMARILLO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    apagarTodos();
}

void loop() {
    digitalWrite(LED_VERDE, HIGH);      // fase verde
    delay(T_VERDE);
    digitalWrite(LED_VERDE, LOW);

    digitalWrite(LED_AMARILLO, HIGH);   // fase amarillo
    delay(T_AMARILLO);
    digitalWrite(LED_AMARILLO, LOW);

    digitalWrite(LED_ROJO, HIGH);       // fase rojo
    delay(T_ROJO);
    digitalWrite(LED_ROJO, LOW);
}
