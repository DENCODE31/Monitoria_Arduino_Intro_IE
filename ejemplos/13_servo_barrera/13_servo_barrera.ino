/*
 * 13_servo_barrera.ino - HC-SR04 + servo: barrera que abre al acercarse
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: combinar sensor de distancia con un actuador, libreria Servo,
 *           histeresis para que la barra no tiemble
 * Montaje: HC-SR04 (VCC=5V, Trig=D9, Echo=D10, GND=GND).
 *          Servo: senal en D3, VCC a fuente de 5 V, GND comun.
 *
 * OJO: el servo NO se alimenta del pin 5V del Arduino. Consume picos de
 *      500 mA y reinicia la placa. Usa una fuente externa de 5 V con GND comun.
 *
 * Servo: pulso de 50 Hz (20 ms). 0.5 ms = 0 grados, 2.5 ms = 180 grados.
 */

#include <Servo.h>                    // libreria que genera el pulso del servo

// ---------- NUMEROS DE LOS PINES ----------
const uint8_t TRIG    = 9;            // TRIG: el Arduino manda el disparo
const uint8_t ECHO    = 10;           // ECHO: el sensor responde
const uint8_t PIN_SERVO = 3;          // senal del servo (D3 admite PWM)

// ---------- VALORES QUE PODEMOS CAMBIAR ----------
const uint16_t CERCA_CM = 15;         // si algo esta a menos de 15 cm, abre
const uint16_t LEJOS_CM = 20;         // si se aleja mas de 20 cm, cierra (histeresis)
const uint16_t INTERVALO_MS = 100;    // mide cada 100 ms

// ---------- ANGULOS DE LA BARRA ----------
const uint8_t ANGULO_CERRADO = 0;     // barra horizontal: paso bloqueado
const uint8_t ANGULO_ABIERTO = 90;    // barra levantada: paso libre

// ---------- MEMORIA DEL PROGRAMA ----------
Servo barrera;                        // objeto que controla el servo
bool abierta = false;                 // estado actual de la barrera
unsigned long tUltimo = 0;            // instante de la ultima medida

// Devuelve la distancia en cm, o -1 si no hubo eco
long medirDistanciaCm() {
    digitalWrite(TRIG, LOW);          // asegura el nivel bajo antes de disparar
    delayMicroseconds(2);

    digitalWrite(TRIG, HIGH);         // pulso de 10 us dispara la medicion
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    // Espera el pulso de eco. Timeout de 30 ms (~5 m maximo)
    unsigned long duracion = pulseIn(ECHO, HIGH, 30000);

    if (duracion == 0) {              // sin eco: objeto lejos o cable suelto
        return -1;
    }
    return duracion / 58;             // 58 us por cm (ida y vuelta del sonido)
}

void setup() {
    pinMode(TRIG, OUTPUT);            // TRIG manda senal: salida
    pinMode(ECHO, INPUT);             // ECHO recibe senal: entrada

    barrera.attach(PIN_SERVO);        // enlaza el servo al pin D3
    barrera.write(ANGULO_CERRADO);    // arranca con la barra cerrada

    Serial.begin(9600);               // abre el monitor serial
    Serial.println(F("Barrera lista. Acerca la mano al sensor."));
}

void loop() {
    if (millis() - tUltimo < INTERVALO_MS) {   // todavia no pasan 100 ms...
        return;                                // sale y vuelve a entrar
    }
    tUltimo = millis();                        // guarda este instante

    long distancia = medirDistanciaCm();        // lectura del sensor

    if (distancia < 0) {                        // no hubo eco
        Serial.println(F("Sin eco"));
        return;
    }

    // Decide con histeresis: abre cerca, cierra solo si se aleja de verdad
    if (!abierta && distancia < CERCA_CM) {
        abierta = true;
        barrera.write(ANGULO_ABIERTO);          // levanta la barra
    } else if (abierta && distancia > LEJOS_CM) {
        abierta = false;
        barrera.write(ANGULO_CERRADO);          // baja la barra
    }

    // Muestra el estado en el monitor serial
    Serial.print(F("Distancia: "));
    Serial.print(distancia);
    Serial.print(F(" cm  barrera="));
    Serial.println(abierta ? F("ABIERTA") : F("CERRADA"));
}
