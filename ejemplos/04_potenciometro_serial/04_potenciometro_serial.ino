/*
 * 04_potenciometro_serial.ino - Lectura analogica y monitor serial
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: analogRead(), map(), Serial.print, actualizacion no bloqueante
 * Montaje: potenciometro (extremos a 5 V y GND, cursor a A0), LED en D9
 */

const uint8_t POT   = A0;
const uint8_t LED   = 9;             // D9 tiene PWM
const uint16_t INTERVALO_MS = 250;   // imprime 4 veces por segundo

unsigned long tUltimo = 0;

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    Serial.println(F("Lectura del potenciometro (0-1023):"));
}

void loop() {
    if (millis() - tUltimo >= INTERVALO_MS) {
        tUltimo = millis();

        int crudo = analogRead(POT);                    // 0..1023
        float voltaje = crudo * (5.0 / 1023.0);         // a voltios
        int brillo = map(crudo, 0, 1023, 0, 255);       // a PWM

        analogWrite(LED, brillo);                       // el LED sigue al potenciometro

        Serial.print(F("ADC="));
        Serial.print(crudo);
        Serial.print(F("  V="));
        Serial.print(voltaje, 2);
        Serial.print(F(" V  PWM="));
        Serial.println(brillo);
    }
}
