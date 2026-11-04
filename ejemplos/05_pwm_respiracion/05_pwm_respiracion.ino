/*
 * 05_pwm_respiracion.ino - Intensidad variable con PWM
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: analogWrite() 0-255, suavizado sin delay, cambio de direccion
 * Montaje: LED en D9 (PWM) con resistencia de 220 ohm a GND
 */

const uint8_t LED = 9;                // D9 soporta PWM
const uint8_t PASO = 3;               // cuanto cambia el brillo por ciclo
const uint16_t INTERVALO_MS = 15;     // velocidad de la transicion

int brillo = 0;
int direccion = 1;                    // 1 sube, -1 baja
unsigned long tUltimo = 0;

void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    if (millis() - tUltimo < INTERVALO_MS) {
        return;                       // aun no toca actualizar: el loop sigue libre
    }
    tUltimo = millis();

    brillo += direccion * PASO;

    if (brillo >= 255) {              // techo: empieza a bajar
        brillo = 255;
        direccion = -1;
    } else if (brillo <= 0) {         // piso: empieza a subir
        brillo = 0;
        direccion = 1;
    }

    analogWrite(LED, brillo);         // duty cycle proporcional al brillo
}
