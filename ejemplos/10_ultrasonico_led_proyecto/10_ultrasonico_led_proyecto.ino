// Sesion del 6 de noviembre: sensor ultrasonico HC-SR04 que enciende un LED.
// Conexiones (las mismas del proyecto final, para no recablear despues):
//   HC-SR04 VCC a 5 V, GND a GND, TRIG al pin 3, ECHO al pin 2.
//   LED en el pin 8 con una resistencia de 220 ohm en serie (pata larga hacia el pin).
// Abre el Monitor Serial a 9600 baudios para ver la distancia.

const int PIN_TRIG = 3;
const int PIN_ECHO = 2;
const int PIN_LED = 8;

// Si algo esta mas cerca que esta distancia, se enciende el LED. Calibren este valor.
const int UMBRAL_CM = 10;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED, OUTPUT);
}

int medirDistanciaCm() {
  // Pulso de 10 microsegundos en TRIG para disparar la medicion
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // ECHO dura tanto como tarda el sonido en ir y volver (maximo 30 ms)
  long duracionUs = pulseIn(PIN_ECHO, HIGH, 30000);
  if (duracionUs == 0) {
    return 400;   // sin eco: no hay nada al frente
  }
  return duracionUs / 58;   // microsegundos a centimetros (ver datasheet)
}

void loop() {
  int cm = medirDistanciaCm();

  Serial.print("distancia (cm): ");
  Serial.println(cm);

  if (cm < UMBRAL_CM) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }

  delay(100);
}
