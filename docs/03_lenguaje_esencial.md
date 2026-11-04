# 💻 Lenguaje esencial de Arduino

Lo mínimo para leer y escribir los 9 ejemplos del repositorio.

---

## 1. Estructura de un sketch

Todo programa `.ino` tiene dos funciones obligatorias:

```cpp
void setup() {
    // Se ejecuta UNA vez al encender o resetear
}

void loop() {
    // Se repite infinitamente
}
```

El IDE agrega `#include <Arduino.h>` automáticamente.

---

## 2. Variables

| Tipo | Tamaño | Rango | Uso |
|---|---|---|---|
| `bool` | 1 B | `true` / `false` | Estados |
| `byte` / `uint8_t` | 1 B | 0 – 255 | Pines, PWM |
| `int` | 2 B | −32.768 – 32.767 | Contadores |
| `unsigned int` / `uint16_t` | 2 B | 0 – 65.535 | Millis cortos |
| `long` | 4 B | ±2.147.483.647 | Tiempo |
| `unsigned long` | 4 B | 0 – 4.294.967.295 | `millis()` |
| `float` | 4 B | ±3.4·10³⁸ | Cálculos |

```cpp
const uint8_t LED_PIN = 13;   // const: no cambia, ocupa menos RAM
```

> En un UNO, **2 KB de SRAM** se agotan rápido con `String`. Prefiere `char[]` y `F("texto")` para constantes.

---

## 3. Entradas y salidas digitales

```cpp
pinMode(13, OUTPUT);        // configura el pin
digitalWrite(13, HIGH);     // 5 V
digitalWrite(13, LOW);      // 0 V
int estado = digitalRead(7); // HIGH o LOW
```

Modos de entrada:

| Modo | Comportamiento |
|---|---|
| `INPUT` | Alta impedancia: necesita resistencia externa |
| `INPUT_PULLUP` | Activa resistencia interna a 5 V → **botón a GND, lógica invertida** |
| `OUTPUT` | Entrega o drena corriente |

---

## 4. Entradas analógicas y PWM

```cpp
int lectura = analogRead(A0);            // 0..1023
analogWrite(9, 128);                     // PWM 50 % (solo pines ~)
int brillo = map(lectura, 0, 1023, 0, 255);  // reescala
```

`map()` **no** limita el rango: si la entrada se sale, la salida también. Usa `constrain(valor, min, max)`.

---

## 5. Tiempo

```cpp
delay(500);          // bloquea 500 ms (no hace nada más)
delayMicroseconds(10);

unsigned long ahora = millis();   // ms desde el arranque
```

`millis()` **no bloquea**, pero se desborda a los ~49.7 días. La comparación segura es por resta:

```cpp
if (millis() - ultimoEvento >= INTERVALO) {
    ultimoEvento = millis();
    // tarea periódica
}
```

---

## 6. Comunicación serial

```cpp
void setup() {
    Serial.begin(9600);        // mismo baudaje que el Monitor Serial
}

void loop() {
    Serial.print("Valor: ");
    Serial.println(analogRead(A0));

    if (Serial.available() > 0) {
        char c = Serial.read();
    }
}
```

| Función | Qué hace |
|---|---|
| `Serial.begin(baud)` | Abre el puerto |
| `Serial.print()` / `println()` | Envía texto |
| `Serial.available()` | Bytes pendientes |
| `Serial.read()` | Lee un byte (−1 si no hay) |
| `Serial.readStringUntil('\n')` | Lee una línea |

> `Serial` usa D0 (RX) y D1 (TX). **No** conectes nada ahí mientras programas.

---

## 7. Control de flujo

```cpp
if (condicion) { ... } else if (otra) { ... } else { ... }

switch (estado) {
    case 0: /* ... */ break;
    case 1: /* ... */ break;
    default: break;
}

for (int i = 0; i < 3; i++) { ... }
while (condicion) { ... }
```

---

## 8. Funciones propias

```cpp
void parpadear(uint8_t pin, uint16_t ms) {
    digitalWrite(pin, HIGH);
    delay(ms);
    digitalWrite(pin, LOW);
    delay(ms);
}
```

Divide el programa en funciones pequeñas: así se depura por partes.

---

## 9. Operadores lógicos

| Operador | Significado |
|---|---|
| `&&` | AND |
| `\|\|` | OR |
| `!` | NOT |
| `==` | Comparación (**no** confundir con `=`) |
| `!=` | Distinto |

---

## 10. Errores de novato más frecuentes

1. Olvidar el `;` al final de la línea.
2. Usar `=` en lugar de `==` dentro de un `if`.
3. Declarar el pin como `OUTPUT` y leerlo.
4. Botón sin `INPUT_PULLUP` ni resistencia → lectura aleatoria.
5. Monitor Serial a distinto baudaje → caracteres basura.
6. `delay()` dentro de `loop()` → todo el sistema se congela.
7. Comparar `millis()` con `>` en vez de por resta → falla al desbordarse.
