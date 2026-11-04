/*
 * 09_control_serial.ino - Control del LED por monitor serial
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: Serial.available(), Serial.read(), switch, comandos de usuario
 * Montaje: LED en D9 (PWM) con resistencia de 220 ohm a GND
 * Comandos: 1=encender  0=apagar  t=alternar  ?=estado  h=ayuda
 */

const uint8_t LED = 9;
const uint8_t NIVEL_ENCENDIDO = 255;

uint8_t brillo = 0;

void imprimirAyuda() {
    Serial.println(F("Comandos:"));
    Serial.println(F("  1  -> encender"));
    Serial.println(F("  0  -> apagar"));
    Serial.println(F("  t  -> alternar"));
    Serial.println(F("  ?  -> estado actual"));
    Serial.println(F("  h  -> esta ayuda"));
}

void setup() {
    pinMode(LED, OUTPUT);
    analogWrite(LED, brillo);
    Serial.begin(9600);
    Serial.println(F("Control serial listo."));
    imprimirAyuda();
}

void loop() {
    if (Serial.available() <= 0) {
        return;                       // no hay comandos pendientes
    }

    char comando = Serial.read();     // lee un caracter

    switch (comando) {
        case '1':
            brillo = NIVEL_ENCENDIDO;
            Serial.println(F("LED encendido"));
            break;

        case '0':
            brillo = 0;
            Serial.println(F("LED apagado"));
            break;

        case 't':
            brillo = (brillo > 0) ? 0 : NIVEL_ENCENDIDO;
            Serial.print(F("Toggle -> "));
            Serial.println(brillo > 0 ? F("ON") : F("OFF"));
            break;

        case '?':
            Serial.print(F("Estado: brillo="));
            Serial.println(brillo);
            break;

        case 'h':
            imprimirAyuda();
            break;

        case '\r':
        case '\n':
            break;                    // ignora saltos de linea del terminal

        default:
            Serial.print(F("Comando desconocido: "));
            Serial.println(comando);
            break;
    }

    analogWrite(LED, brillo);         // aplica el estado
}
