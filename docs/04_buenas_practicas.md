# 🛠️ Buenas prácticas desde el primer día

Reglas cortas que evitan el 80 % de los problemas en los laboratorios.

---

## 1. No uses `delay()` para todo

`delay()` congela el microcontrolador: no lee botones, no actualiza el display, no atiende el serial. Sirve para ejemplos de un solo LED, pero en cuanto hay dos tareas se vuelve un problema.

```cpp
// ❌ Bloqueante: el botón solo se lee 2 veces por segundo
digitalWrite(LED, HIGH); delay(500);
digitalWrite(LED, LOW);  delay(500);

// ✅ No bloqueante: el loop corre miles de veces por segundo
const uint16_t INTERVALO = 500;
unsigned long ultimoCambio = 0;
bool estadoLed = false;

void loop() {
    if (millis() - ultimoCambio >= INTERVALO) {
        ultimoCambio = millis();
        estadoLed = !estadoLed;
        digitalWrite(LED, estadoLed);
    }
    leerBoton();   // se ejecuta siempre
}
```

---

## 2. Antirrebote (debounce) del pulsador

Un pulsador mecánico genera varios flancos en pocos milisegundos. Si no se filtra, una pulsación cuenta como 5 o 10.

```cpp
if (digitalRead(BOTON) == LOW && millis() - ultimaLectura > 30) {
    ultimaLectura = millis();
    // acción válida
}
```

Filtro por software: ignora cambios más rápidos que **20–50 ms**.

---

## 3. Usa `INPUT_PULLUP`

```cpp
pinMode(BOTON, INPUT_PULLUP);   // botón entre pin y GND
```

- Ahorra la resistencia externa de 10 kΩ.
- La lógica se invierte: **LOW = presionado**.
- Evita entradas flotantes (lecturas aleatorias).

---

## 4. Nombra los pines con constantes

```cpp
const uint8_t LED_ROJO   = 8;
const uint8_t LED_VERDE  = 9;
const uint8_t BOTON      = 7;
```

Cambiar el cable de pin pasa de ser una cacería de números a una línea de código.

---

## 5. Protecciones eléctricas

| Regla | Por qué |
|---|---|
| Resistencia en serie con cada LED (220 Ω – 1 kΩ) | Sin ella el LED y el pin se destruyen |
| GND común entre placa y fuente externa | Sin referencia, las señales no tienen sentido |
| Fuente externa para motores y servos | El regulador del UNO no entrega esa corriente |
| No alimentar nada por `3.3V` que consuma > 50 mA | El regulador interno se daña |
| Desconectar USB antes de mover cables | Evita cortos en caliente |

---

## 6. Depura con el Monitor Serial

```cpp
Serial.begin(9600);
Serial.print("Estado: "); Serial.println(estado);
```

- Pon `Serial.begin()` una sola vez, en `setup()`.
- Usa el mismo baudaje en el Monitor Serial.
- Imprime **valores**, no solo "hola": `"ADC="`, luego el número.
- Quita los `Serial.print` de producción: consumen tiempo y RAM.

---

## 7. Estructura recomendada del sketch

```cpp
// 1. Constantes y pines
const uint8_t LED = 13;

// 2. Variables de estado
bool encendido = false;
unsigned long ultimoEvento = 0;

// 3. setup()
void setup() { }

// 4. loop() delgado: solo orquesta
void loop() {
    actualizarEntradas();
    actualizarSalidas();
}

// 5. Funciones auxiliares
void actualizarEntradas() { }
void actualizarSalidas()  { }
```

Un `loop()` de 30 líneas se entiende; uno de 200 no.

---

## 8. Máquina de estados (para secuencias)

Cuando el comportamiento depende del tiempo o de eventos, usa estados explícitos:

```cpp
enum Estado { REPOSO, ACTIVO, ALARMA };
Estado estado = REPOSO;

void loop() {
    switch (estado) {
        case REPOSO: /* ... */ break;
        case ACTIVO: /* ... */ break;
        case ALARMA: /* ... */ break;
    }
}
```

Es la misma estructura que verás en Sistemas Digitales y en Estructuras Computacionales.

---

## 9. Versiona tu código

```bash
git init
git add .
git commit -m "feat: primer montaje con LED y botón"
```

Commits pequeños y descriptivos. Un repositorio por práctica, no una carpeta llamada `arduino_final_final_v2`.

---

## 10. Checklist antes de cargar

- [ ] ¿Cada LED tiene su resistencia?
- [ ] ¿GND de la fuente externa unido al GND del Arduino?
- [ ] ¿El pin del código coincide con el cable físico?
- [ ] ¿La placa y el puerto seleccionados son correctos?
- [ ] ¿El Monitor Serial está a **9600**?
- [ ] ¿Hay algún corto entre 5 V y GND?
