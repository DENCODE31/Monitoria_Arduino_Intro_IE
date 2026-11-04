/*
 * 08_ultrasonido.ino - Medidor de distancia con HC-SR04
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: pulseIn(), timeout, promedio de lecturas, actuador por umbral
 * Montaje: HC-SR04 (VCC=5V, Trig=D9, Echo=D10, GND=GND), LED en D13
 */

const uint8_t TRIG = 9;
const uint8_t ECHO = 10;
const uint8_t LED  = 13;

const uint16_t UMBRAL_CM = 20;        // enciende el LED si hay algo mas cerca
const uint16_t INTERVALO_MS = 200;

unsigned long tUltimo = 0;

// Devuelve la distancia en cm, o -1 si no hubo eco
long medirDistanciaCm() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG, HIGH);         // pulso de 10 us dispara la medicion
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    // Espera el pulso de eco. Timeout de 30 ms (~5 m maximo)
    unsigned long duracion = pulseIn(ECHO, HIGH, 30000);

    if (duracion == 0) {
        return -1;                    // sensor fuera de rango o desconectado
    }
    return duracion / 58;             // velocidad del sonido: 58 us por cm
}

void setup() {
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    Serial.println(F("Medidor de distancia iniciado."));
}

void loop() {
    if (millis() - tUltimo < INTERVALO_MS) {
        return;
    }
    tUltimo = millis();

    // Promedio de 3 mediciones validas para filtrar ruido
    long suma = 0;
    uint8_t validas = 0;

    for (uint8_t i = 0; i < 3; i++) {
        long d = medirDistanciaCm();
        if (d > 0) {
            suma += d;
            validas++;
        }
        delay(10);
    }

    if (validas == 0) {
        Serial.println(F("Sin eco: revisa el sensor."));
        digitalWrite(LED, LOW);
        return;
    }

    long promedio = suma / validas;
    digitalWrite(LED, promedio < UMBRAL_CM ? HIGH : LOW);

    Serial.print(F("Distancia="));
    Serial.print(promedio);
    Serial.println(F(" cm"));
}
