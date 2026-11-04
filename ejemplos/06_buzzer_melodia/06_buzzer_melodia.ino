/*
 * 06_buzzer_melodia.ino - Melodia con buzzer pasivo
 * Monitoria: Instalacion y manejo de Arduino - Intro. Ing. Electronica (UNAL)
 * Placa: Arduino UNO R3
 * Concepto: tone(), arreglos, maquina de estados con millis()
 * Montaje: buzzer pasivo entre D8 y GND
 */

const uint8_t BUZZER = 8;
const uint16_t DURACION_NOTA = 220;   // ms por nota
const uint16_t PAUSA_ENTRE_NOTAS = 30;

// Frecuencias en Hz. 0 = silencio
const uint16_t MELODIA[] = {
    262, 294, 330, 349, 392, 440, 494, 523,   // escala ascendente (C4 - C5)
    523, 494, 440, 392, 349, 330, 294, 262,   // escala descendente
     0                                        // pausa final antes de repetir
};
const uint8_t NUM_NOTAS = sizeof(MELODIA) / sizeof(MELODIA[0]);

uint8_t indice = 0;
unsigned long tUltimo = 0;

void tocarNota(uint8_t i) {
    uint16_t frecuencia = MELODIA[i];
    if (frecuencia == 0) {
        noTone(BUZZER);
    } else {
        tone(BUZZER, frecuencia, DURACION_NOTA - PAUSA_ENTRE_NOTAS);
    }
}

void setup() {
    pinMode(BUZZER, OUTPUT);
    tUltimo = millis();
    tocarNota(0);
}

void loop() {
    if (millis() - tUltimo < DURACION_NOTA) {
        return;                       // la nota aun esta sonando
    }
    tUltimo = millis();

    indice = (indice + 1) % NUM_NOTAS;  // avanza y vuelve al inicio
    tocarNota(indice);
}
