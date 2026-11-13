/*
 * 14_servo_buzzer.ino - Barrera con servo y aviso sonoro
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: integrar sensor, servo y buzzer en un solo programa no bloqueante
 * Montaje: HC-SR04 (VCC=5V, Trig=D9, Echo=D10, GND=GND).
 *          Servo: senal en D3, VCC a fuente externa de 5 V, GND comun.
 *          Buzzer pasivo en D8.
 *
 * OJO: el servo NO se alimenta del pin 5V del Arduino. Consume picos de
 *      500 mA y reinicia la placa. Usa una fuente externa de 5 V con GND comun.
 *
 * Buzzer pasivo: necesita una frecuencia (tone). Un buzzer activo solo necesita
 * HIGH; en ese caso cambia tone() por digitalWrite y noTone() por LOW.
 *
 * Aviso sonoro: un pitido agudo al abrir y otro grave al cerrar. El pitido se
 * apaga con millis(), no con delay(), para no frenar la medicion.
 */

#include <Servo.h>                    // libreria que genera el pulso del servo

// ---------- NUMEROS DE LOS PINES ----------
const uint8_t TRIG       = 9;         // TRIG: el Arduino manda el disparo
const uint8_t ECHO       = 10;        // ECHO: el sensor responde
const uint8_t PIN_SERVO  = 3;         // senal del servo (D3 admite PWM)
const uint8_t PIN_BUZZER = 8;         // buzzer pasivo

// ---------- VALORES QUE PODEMOS CAMBIAR ----------
const uint16_t CERCA_CM = 15;         // si algo esta a menos de 15 cm, abre
const uint16_t LEJOS_CM = 20;         // si se aleja mas de 20 cm, cierra (histeresis)
const uint16_t INTERVALO_MS = 100;    // mide cada 100 ms

// ---------- ANGULOS DE LA BARRA ----------
const uint8_t ANGULO_CERRADO = 0;     // barra horizontal: paso bloqueado
const uint8_t ANGULO_ABIERTO = 90;    // barra levantada: paso libre

// ---------- SONIDOS ----------
const uint16_t FREQ_ABRE   = 1500;    // Hz al abrir (agudo)
const uint16_t FREQ_CIERRA = 800;     // Hz al cerrar (grave)
const uint16_t DURACION_MS = 150;     // cuanto dura cada pitido

// ---------- MEMORIA DEL PROGRAMA ----------
Servo barrera;                        // objeto que controla el servo
bool abierta = false;                 // estado actual de la barrera
unsigned long tUltimo = 0;            // instante de la ultima medida

bool pitando = false;                 // hay un pitido en curso
unsigned long tPitido = 0;            // instante en que empezo el pitido

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

// Arranca un pitido sin bloquear el programa
void pitido(uint16_t frecuencia) {
    tone(PIN_BUZZER, frecuencia);     // genera la onda cuadrada
    tPitido = millis();               // guarda cuando empezo
    pitando = true;                   // marca que hay un pitido activo
}

void setup() {
    pinMode(TRIG, OUTPUT);            // TRIG manda senal: salida
    pinMode(ECHO, INPUT);             // ECHO recibe senal: entrada
    pinMode(PIN_BUZZER, OUTPUT);      // buzzer: salida

    barrera.attach(PIN_SERVO);        // enlaza el servo al pin D3
    barrera.write(ANGULO_CERRADO);    // arranca con la barra cerrada

    Serial.begin(9600);               // abre el monitor serial
    Serial.println(F("Barrera con aviso sonoro lista. Acerca la mano al sensor."));
}

void loop() {
    // 1. apaga el pitido cuando ya paso su duracion (no bloqueante)
    if (pitando && millis() - tPitido >= DURACION_MS) {
        noTone(PIN_BUZZER);           // silencia el buzzer
        pitando = false;              // ya no hay pitido activo
    }

    // 2. mide cada 100 ms
    if (millis() - tUltimo < INTERVALO_MS) {
        return;
    }
    tUltimo = millis();

    long distancia = medirDistanciaCm();        // lectura del sensor

    if (distancia < 0) {                        // no hubo eco
        Serial.println(F("Sin eco"));
        return;
    }

    // 3. decide con histeresis y avisa con un sonido distinto cada caso
    if (!abierta && distancia < CERCA_CM) {
        abierta = true;
        barrera.write(ANGULO_ABIERTO);          // levanta la barra
        pitido(FREQ_ABRE);                      // pitido agudo al abrir
    } else if (abierta && distancia > LEJOS_CM) {
        abierta = false;
        barrera.write(ANGULO_CERRADO);          // baja la barra
        pitido(FREQ_CIERRA);                    // pitido grave al cerrar
    }

    // 4. muestra el estado en el monitor serial
    Serial.print(F("Distancia: "));
    Serial.print(distancia);
    Serial.print(F(" cm  barrera="));
    Serial.println(abierta ? F("ABIERTA") : F("CERRADA"));
}
