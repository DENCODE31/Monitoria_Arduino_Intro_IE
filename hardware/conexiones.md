# 🔗 Conexiones de cada montaje

Todos los montajes usan la misma protoboard y el mismo criterio:

- **Rojo** → 5 V
- **Negro / azul** → GND
- **Amarillo / verde** → señal

---

## 1. Blink (LED integrado)

Sin cableado. El LED `L` está soldado en la placa y conectado a **D13**.

```
Arduino UNO ── USB ── PC
        └── LED "L" (D13) parpadea
```

---

## 2. Semáforo peatonal

```
        Arduino UNO
        ┌──────────┐
   D8 ──┤ 220 Ω ├──────►|──── GND      LED ROJO
   D9 ──┤ 220 Ω ├──────►|──── GND      LED AMARILLO
  D10 ──┤ 220 Ω ├──────►|──── GND      LED VERDE
        └──────────┘
```

| LED | Pin | Resistencia | Ánodo | Cátodo |
|---|---|---|---|---|
| Rojo | D8 | 220 Ω | D8 | GND |
| Amarillo | D9 | 220 Ω | D9 | GND |
| Verde | D10 | 220 Ω | D10 | GND |

> El cátodo (pata corta) va a GND. El ánodo (pata larga) va al pin a través de la resistencia.

---

## 3. Botón con antirrebote

```
   D2 ──────┬──────[ pulsador ]────── GND
            │
       (pull-up interno)

  D13 ──┤ 220 Ω ├──►|── GND   (LED integrado, opcional externo)
```

| Elemento | Conexión |
|---|---|
| Pulsador | entre **D2** y **GND** |
| Modo del pin | `INPUT_PULLUP` |
| Lógica | `LOW` = presionado |

> No se necesita resistencia externa: se usa la interna del ATmega328P.

---

## 4. Potenciómetro + monitor serial

```
        5 V ──┬─────────────┐
              │             │
           ┌──┴──┐          │
           │ 10k │◄── cursor ──► A0
           └──┬──┘          │
              │             │
             GND ───────────┘

   D9 ──┤ 220 Ω ├──►|── GND   (LED indicador de nivel, opcional)
```

| Pata del potenciómetro | Conexión |
|---|---|
| Extremo 1 | 5 V |
| Extremo 2 | GND |
| Cursor (central) | **A0** |

---

## 5. PWM: respiración del LED

```
   D9 (~PWM) ──┤ 220 Ω ├──►|── GND
```

| Elemento | Conexión |
|---|---|
| LED | ánodo → resistencia → **D9**, cátodo → GND |

> D9 es uno de los 6 pines PWM. En otros pines `analogWrite` no funciona.

---

## 6. Buzzer con melodía

```
   D8 ──────►| buzzer (+) 
              buzzer (−) ──── GND
```

| Elemento | Conexión |
|---|---|
| Buzzer pasivo | positivo → **D8**, negativo → GND |

> Buzzer **pasivo** = necesita `tone()` (frecuencia). Buzzer **activo** = suena con `digitalWrite(HIGH)` y no permite melodías.

---

## 7. Alarma con LDR

```
        5 V ────┬────────────┐
                 │            │
              [ LDR ]      [ 10 kΩ ]
                 │            │
                 ├────────────┴──── A0
                 │
                GND

   D13 ──┤ 220 Ω ├──►|── GND     LED de alarma
   D9  ────────►| buzzer ── GND
```

| Elemento | Conexión |
|---|---|
| LDR | entre 5 V y **A0** |
| Resistencia 10 kΩ | entre **A0** y GND |
| LED | D13 con 220 Ω |
| Buzzer | D9 |

> Es un divisor de tensión: más luz → menor resistencia del LDR → mayor voltaje en A0.

---

## 8. Sensor ultrasónico HC-SR04

```
        HC-SR04                    Arduino UNO
        ┌──────┐
   VCC ─┤      ├──── 5 V
   Trig ┤      ├──── D9
   Echo ┤      ├──── D10
   GND ─┤      ├──── GND
        └──────┘

   D13 ──┤ 220 Ω ├──►|── GND   (LED que enciende si hay objeto cerca)
```

| Pin HC-SR04 | Arduino |
|---|---|
| VCC | 5 V |
| Trig | D9 |
| Echo | D10 |
| GND | GND |

> El Echo entrega 5 V. Si usaras un ESP32 (3.3 V) necesitarías divisor de tensión; con el UNO no hay problema.

---

## 9. Control por monitor serial

```
   D9 (~PWM) ──┤ 220 Ω ├──►|── GND
   USB ── PC (Monitor Serial 9600 baudios)
```

| Elemento | Conexión |
|---|---|
| LED | D9 con 220 Ω |
| Comandos | `1` encender · `0` apagar · `t` alternar · `?` estado |

---

## Verificación antes de conectar el USB

1. ¿Cada LED tiene resistencia?
2. ¿Todos los GND están unidos?
3. ¿5 V y GND están separados (sin puente)?
4. ¿El pin del código coincide con el pin físico?
5. ¿La placa está sobre una superficie aislante?
