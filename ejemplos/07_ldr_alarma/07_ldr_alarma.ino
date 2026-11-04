/*
 * 07_ldr_alarma.ino - Sensor de luz con alarma e histeresis
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: analogRead(), umbral con histeresis, actuadores LED y buzzer
 * Montaje: LDR entre 5 V y A0, 10 kohm entre A0 y GND, LED en D13, buzzer en D9
 */

const uint8_t LDR    = A0;
const uint8_t LED    = 13;
const uint8_t BUZZER = 9;

const int UMBRAL     = 500;   // calibrar con el monitor serial
const int HISTERESIS = 40;    // evita encendido/apagado continuo cerca del umbral

bool alarma = false;
unsigned long tUltimo = 0;
const uint16_t INTERVALO_MS = 200;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    Serial.begin(9600);
    Serial.println(F("Aproxime la mano al LDR para activar la alarma."));
}

void loop() {
    if (millis() - tUltimo < INTERVALO_MS) {
        return;
    }
    tUltimo = millis();

    int luz = analogRead(LDR);    // oscuro -> valor bajo (LDR arriba)

    // Histeresis: para encender exige bajar de UMBRAL - H, para apagar subir de UMBRAL + H
    if (!alarma && luz < (UMBRAL - HISTERESIS)) {
        alarma = true;
    } else if (alarma && luz > (UMBRAL + HISTERESIS)) {
        alarma = false;
    }

    digitalWrite(LED, alarma ? HIGH : LOW);
    if (alarma) {
        tone(BUZZER, 1000);
    } else {
        noTone(BUZZER);
    }

    Serial.print(F("Luz="));
    Serial.print(luz);
    Serial.print(F("  Alarma="));
    Serial.println(alarma ? F("ON") : F("OFF"));
}
