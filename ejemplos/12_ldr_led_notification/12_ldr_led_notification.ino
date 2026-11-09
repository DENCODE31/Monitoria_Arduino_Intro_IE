// ---------- PINES Y UMBRAL ----------
const int PIN_LDR = /* designa aquí tu pin */;
const int PIN_LED = /* designa aquí tu pin */;
const int UMBRAL  = /* valor que separa "poca luz" de "mucha luz" */;

// Memoria del programa: guarda cómo estaba la luz la última vez que miramos.
// true = había poca luz, false = había mucha luz
bool estadoAnterior = false;

void setup() {
  Serial.begin(/* velocidad del monitor serial */);
  pinMode(/* pin */, /* ¿entrada o salida? */);   // LDR
  pinMode(/* pin */, /* ¿entrada o salida? */);   // LED
}

void loop() {
  int valor = analogRead(/* pin de la LDR */);

  // pocaLuz vale true si la LDR está recibiendo poca luz, y false si recibe mucha.
  // Se decide comparando el valor leído con el umbral.
  bool pocaLuz = (valor < UMBRAL);

  // Solo entramos aquí cuando la luz CAMBIÓ respecto a la última vez
  if (/* ¿el estado actual es distinto del anterior? */) {
    if (pocaLuz) {
      Serial.println(/* mensaje para poca luz */);
    } else {
      Serial.println(/* mensaje para mucha luz */);
    }
    estadoAnterior = /* ¿qué debe recordar el programa ahora? */;
  }

  digitalWrite(/* pin */, /* qué valor debe recibir el LED */);

  delay(50);
}
