# 🔌 Hardware: Arduino UNO R3

Todo lo que hay que saber antes de conectar el primer cable.

---

## 1. Ficha técnica

| Característica | Valor |
|---|---|
| Microcontrolador | ATmega328P (AVR, 8 bits) |
| Frecuencia | 16 MHz |
| Memoria Flash | 32 KB (0.5 KB usados por el bootloader) |
| SRAM | 2 KB |
| EEPROM | 1 KB |
| Voltaje de operación | 5 V |
| Voltaje de entrada (Vin) | 7 – 12 V recomendado (límite 6 – 20 V) |
| Pines digitales | 14 (D0 – D13) |
| Pines PWM | 6 (D3, D5, D6, D9, D10, D11) |
| Entradas analógicas | 6 (A0 – A5), ADC de 10 bits |
| Corriente por pin | **20 mA recomendado, 40 mA absoluto** |
| Corriente total del chip | **200 mA** |
| Corriente salida 5 V | ~400 mA (limitada por el regulador y el USB) |
| Comunicación | UART (D0/D1), I²C (A4/A5), SPI (D10–D13) |

---

## 2. Mapa de pines

```
                        ┌─────────────────────────┐
                        │      ARDUINO UNO R3     │
      ┌─────────────────┤                         ├─────────────────┐
      │  D0  RX         │                         │  A0             │
      │  D1  TX         │                         │  A1             │
      │  D2  ───────────┤                         ├───────── A2     │
      │  D3  ~ PWM      │        ATmega328P       │  A3             │
      │  D4  ───────────┤                         ├───────── A4 SDA │
      │  D5  ~ PWM      │                         │  A5 SCL         │
      │  D6  ~ PWM      │                         │                 │
      │  D7  ───────────┤                         │  5V             │
      │  D8  ───────────┤                         │  GND            │
      │  D9  ~ PWM      │                         │  GND            │
      │  D10 ~ PWM / SS │                         │  Vin            │
      │  D11 ~ PWM/MOSI │                         │  3.3V           │
      │  D12    MISO    │                         │  RESET          │
      │  D13    SCK/LED │                         │  IOREF          │
      └─────────────────┴─────────────────────────┴─────────────────┘
                          USB          JACK 7-12V
```

> `~` significa que el pin soporta **PWM** (`analogWrite`). El LED integrado está en **D13** (`LED_BUILTIN`).

---

## 3. Límites eléctricos (lo que evita quemar la placa)

1. **Un LED nunca va directo a 5 V.** Siempre con resistencia.
   ```
   R = (5 V − V_LED) / I
   LED rojo (V ≈ 2 V, I = 15 mA) → R = (5 − 2) / 0.015 ≈ 200 Ω → usar 220 Ω
   ```
2. **No alimentar motores, servos ni tiras LED desde el pin 5V.** Usa fuente externa y une los **GND**.
3. **No conectar 5 V a un pin configurado como salida en LOW.** Es un corto: el pin se destruye.
4. **No inyectar más de 5 V en un pin digital ni en una entrada analógica.**
5. **3.3 V solo entrega ~50 mA.** No alimentes módulos grandes desde ahí.
6. Antes de energizar: revisa que **VCC y GND nunca estén puenteados**.

---

## 4. Alimentación

| Fuente | Cuándo |
|---|---|
| USB (5 V) | Programar y montajes de bajo consumo |
| Jack DC 7–12 V | Montajes con motores o relés |
| Pin `Vin` | Batería externa (7–12 V) |
| Pin `5V` | Solo como **entrada** desde fuente regulada de 5 V, nunca junto con USB idealmente |

El regulador del UNO disipa en calor: con 12 V de entrada y consumo alto se calienta. Prefiere 9 V.

---

## 5. Entradas analógicas

- Resolución: **10 bits → 0 a 1023**.
- Referencia por defecto: **5 V** → 1 LSB ≈ **4.88 mV**.
- `analogRead(A0)` devuelve 0 con 0 V y 1023 con 5 V.
- Para sensores de 3.3 V puedes usar `analogReference(EXTERNAL)` con `AREF`, o aceptar la pérdida de resolución.

```cpp
int valor = analogRead(A0);                  // 0..1023
float voltaje = valor * (5.0 / 1023.0);      // a voltios
```

---

## 6. PWM

- `analogWrite(pin, 0..255)` → duty cycle de 0 % a 100 %.
- Frecuencia por defecto: ~490 Hz (D5 y D6: ~980 Hz).
- **No es una DAC**: es una onda cuadrada filtrable. Para audio usa `tone()`.
- `analogWrite` **no** funciona en D2, D4, D7, D8, D12, D13.

---

## 7. Diferencias con clones

| Aspecto | Original | Clon típico |
|---|---|---|
| USB-Serie | ATmega16U2 | CH340 / CP2102 |
| Driver | Incluido | Requiere CH340 (ver instalación) |
| Puerto Linux | `/dev/ttyACM0` | `/dev/ttyUSB0` |
| Calidad del regulador | Buena | Variable: no exceder 9 V |
| Precio (COP) | ~$90.000 – $130.000 | ~$30.000 – $45.000 |

Funcionalmente son iguales para esta monitoría. Si el clon no carga programas, el 90 % de las veces es **driver CH340** o **cable sin datos**.

---

## 8. Seguridad del montaje

- Conecta **GND primero**, desconéctalo de último.
- Desconecta el USB antes de mover cables.
- No trabajes con la placa sobre superficies metálicas.
- Usa gafas si vas a cortar o soldar (no aplica en protoboard).
- Si hueles a quemado o ves humo: **desconecta el USB**, no lo pienses.
