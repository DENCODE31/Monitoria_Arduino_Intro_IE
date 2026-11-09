// Sesion del 6 de noviembre: variante del ejemplo 11 con mensajes en el Monitor Serial.
// Conexiones (las mismas del proyecto final):
//   LDR de 5 V a A0, y resistencia de 10 kohm de A0 a GND (divisor de voltaje).
//   LED en el pin 8 con una resistencia de 220 ohm en serie (pata larga hacia el pin).
// Con mucha luz la lectura es alta; al taparla, baja. Rango de 0 a 1023.
// Abre el Monitor Serial a 9600 baudios: imprime "poca luz" al tapar la LDR.

const int PIN_LDR = A0;
const int PIN_LED = 8;

// Si la lectura baja de este valor, se considera que hay poca luz.
// Calibren: pongan el valor a mitad de camino entre la lectura con luz y con la LDR tapada.
const int UMBRAL = 200;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  int luz = analogRead(PIN_LDR);

  if (luz < UMBRAL) {
    Serial.println("poca luz");
    digitalWrite(PIN_LED, HIGH);
  } else {
    Serial.println("muchas luces");
    digitalWrite(PIN_LED, LOW);
  }

  delay(500);
}
