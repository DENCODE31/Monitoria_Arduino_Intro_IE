/*
 * 03_boton_antirrebote.ino - Boton con filtro por software
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: entrada digital, INPUT_PULLUP, antirrebote con millis(), contador
 * Montaje: pulsador entre D2 y GND, LED en D13 con resistencia de 220 ohm
 */

const uint8_t BOTON   = 2;
const uint8_t LED     = 13;
const uint16_t DEBOUNCE_MS = 30;    // ignora rebotes mas rapidos que 30 ms

bool lecturaAnterior = HIGH;
unsigned long tUltimoCambio = 0;
uint16_t contador = 0;

void setup() {
    pinMode(BOTON, INPUT_PULLUP);   // resistencia interna: LOW = presionado
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
    Serial.println(F("Listo. Presiona el boton."));
}

void loop() {
    bool lectura = digitalRead(BOTON);

    // Solo acepta un cambio si paso el tiempo de antirrebote
    if (lectura != lecturaAnterior && (millis() - tUltimoCambio) > DEBOUNCE_MS) {
        tUltimoCambio = millis();
        lecturaAnterior = lectura;

        if (lectura == LOW) {              // flanco de bajada = pulsacion
            contador++;
            digitalWrite(LED, HIGH);
            Serial.print(F("Pulsaciones: "));
            Serial.println(contador);
        } else {                           // flanco de subida = liberacion
            digitalWrite(LED, LOW);
        }
    }
}
