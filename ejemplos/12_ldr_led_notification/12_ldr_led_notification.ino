// ---------- PINES Y UMBRAL ----------
const int PIN_LDR = A0;
const int PIN_LED = 8;
const int UMBRAL  = 200;

// Memoria del programa: guarda cómo estaba la luz la última vez que miramos.
// true = había poca luz, false = había mucha luz
bool estadoAnterior = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LDR, INPUT);   // LDR
  pinMode(PIN_LED, OUTPUT);  // LED
}

void loop() {
  int valor = analogRead(PIN_LDR);

  // pocaLuz vale true si la LDR está recibiendo poca luz, y false si recibe mucha.
  // Se decide comparando el valor leído con el umbral.
  bool pocaLuz = (valor < UMBRAL);

  // Solo entramos aquí cuando la luz CAMBIÓ respecto a la última vez
  if (pocaLuz != estadoAnterior) {
    if (pocaLuz) {
      Serial.println("poca luz");
    } else {
      Serial.println("muchas luces");
    }
    estadoAnterior = pocaLuz;
  }

  digitalWrite(PIN_LED, pocaLuz);

  delay(50);
}
