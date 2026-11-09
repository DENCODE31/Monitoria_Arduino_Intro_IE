# Ejemplos de código

Sketches progresivos. Cada carpeta contiene un archivo `.ino` con el mismo nombre de la carpeta, como exige Arduino.

| # | Carpeta | Concepto | Pines |
|---|---|---|---|
| 01 | `01_blink` | `setup()` / `loop()`, salida digital | D13 |
| 02 | `02_semaforo_peatonal` | Secuencia temporizada | D8, D9, D10 |
| 03 | `03_boton_antirrebote` | Entrada digital, `INPUT_PULLUP`, `millis()` | D2, D13 |
| 04 | `04_potenciometro_serial` | `analogRead`, `map`, `Serial` | A0, D9 |
| 05 | `05_pwm_respiracion` | `analogWrite`, PWM | D9 |
| 06 | `06_buzzer_melodia` | `tone()`, arreglos, máquina de estados | D8 |
| 07 | `07_ldr_alarma` | Sensor analógico, umbral, histéresis | A0, D9, D13 |
| 08 | `08_ultrasonido` | `pulseIn()`, sensores de tiempo | D9, D10, D13 |
| 09 | `09_control_serial` | Comandos por puerto serial | D9 |
| 10 | `10_ultrasonico_led_proyecto` | `pulseIn()`, umbral de distancia, pines del proyecto final | D3, D2, D8 |
| 11 | `11_ldr_led_proyecto` | `analogRead`, umbral de luz, pines del proyecto final | A0, D8 |
| 12 | `12_ldr_led_notification` | Mensajes en el Monitor Serial según la luz | A0, D8 |

## Cómo abrir un ejemplo

**Opción A — IDE:**

1. `Archivo → Abrir` y selecciona el `.ino`.
2. Verifica **Placa: Arduino Uno** y el puerto.
3. Sube con **→**.

**Opción B — terminal (`arduino-cli`):**

```bash
arduino-cli compile --fqbn arduino:avr:uno ejemplos/05_pwm_respiracion
arduino-cli upload  --fqbn arduino:avr:uno -p /dev/ttyACM0 ejemplos/05_pwm_respiracion
```

## Orden sugerido

```
01 → 02 → 03 → 04 → 05 → 06 → 07 → 08 → 09
```

Los ejemplos 3, 5, 6 y 9 introducen `millis()`; a partir de ahí no se usa `delay()` para tareas múltiples.

Los ejemplos 10 y 11 usan los pines del proyecto final (maqueta del parqueadero), para no recablear después.
