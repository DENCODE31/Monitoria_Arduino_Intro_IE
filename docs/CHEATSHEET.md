# 🧰 Cheatsheet — Arduino UNO R3

Una página para tener al lado mientras programas.

---

## Estructura

```cpp
const uint8_t LED = 13;

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
}
```

---

## Pines

| Necesito | Función | Pines |
|---|---|---|
| Encender/apagar | `digitalWrite` | D2 – D13 |
| Leer botón | `digitalRead` | D2 – D13 |
| Intensidad variable | `analogWrite` (0–255) | **D3, D5, D6, D9, D10, D11** |
| Leer sensor | `analogRead` (0–1023) | **A0 – A5** |
| Serial | `Serial` | D0 (RX), D1 (TX) |
| LED integrado | `LED_BUILTIN` | D13 |

---

## Funciones clave

```cpp
pinMode(pin, OUTPUT | INPUT | INPUT_PULLUP);
digitalWrite(pin, HIGH | LOW);
digitalRead(pin);                  // HIGH / LOW

analogRead(A0);                    // 0..1023
analogWrite(pinPWM, 0..255);       // duty cycle
map(x, in_min, in_max, out_min, out_max);
constrain(x, min, max);

delay(ms);
millis();                          // ms desde el arranque
delayMicroseconds(us);
pulseIn(pin, HIGH, timeout);       // duración de un pulso

tone(pin, frecuencia, duracion);   // Hz, ms
noTone(pin);

Serial.begin(9600);
Serial.print(x);  Serial.println(x);
Serial.available();  Serial.read();
```

---

## Fórmulas

```
Resistencia LED:     R = (5 − V_LED) / I_LED
LED rojo 2 V, 15 mA → 220 Ω
Corriente pin:       máx 20 mA recomendado / 40 mA absoluto
ADC:                 1 LSB ≈ 4.88 mV  (5 V / 1024)
PWM:                 duty = valor / 255 · 100 %
```

---

## Sensores del repositorio

| Sensor | Conexión | Lectura |
|---|---|---|
| Pulsador | pin ↔ GND (`INPUT_PULLUP`) | `digitalRead` (LOW = presionado) |
| Potenciómetro | extremos a 5 V y GND, cursor a Ax | `analogRead` 0–1023 |
| LDR | divisor con 10 kΩ a GND, nodo a Ax | `analogRead`, umbral |
| HC-SR04 | Trig → D9, Echo → D10 | `pulseIn`, `cm = µs / 58` |
| Buzzer pasivo | pin → buzzer → GND | `tone()` |
| Buzzer activo | pin → buzzer → GND | `digitalWrite` |

---

## Errores rápidos

| Síntoma | Revisa |
|---|---|
| `(no ports available)` | Cable USB, driver CH340, placa conectada |
| `Permission denied` en Linux | `sudo usermod -aG dialout $USER` + reiniciar sesión |
| `not in sync` | Board/puerto incorrecto, Monitor Serial abierto |
| Monitor Serial con basura | Baudaje distinto a `Serial.begin()` |
| LED no enciende | Polaridad invertida, falta resistencia, pin equivocado |
| Botón lee aleatorio | Falta `INPUT_PULLUP` o resistencia |
| `analogWrite` no hace nada | Pin sin PWM (usa D3, D5, D6, D9, D10, D11) |
| Servo tiembla | Alimentación insuficiente: fuente externa |

---

## Antirrebote mínimo

```cpp
if (digitalRead(BOTON) == LOW && millis() - tUltimo > 30) {
    tUltimo = millis();
}
```

## Tarea periódica sin `delay()`

```cpp
if (millis() - tUltimo >= 500) {
    tUltimo = millis();
    // hacer algo cada 500 ms
}
```
