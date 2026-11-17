# 🖥️ Pantallas I2C en Arduino UNO

Guía para los ejemplos `15_lcd_i2c` y `16_oled_i2c`.

## Cableado

En el UNO el bus I2C está fijo: **SDA = A4, SCL = A5**. Por eso `Wire.begin()` no lleva argumentos.

| Módulo | VCC | GND | SDA | SCL |
|---|---|---|---|---|
| LCD 16x2 + PCF8574 | 5V | GND | A4 | A5 |
| OLED SSD1306 | 3.3 V o 5 V, según regulador | GND | A4 | A5 |

## Direcciones

| Dispositivo | Dirección habitual | Alternativa |
|---|---|---|
| LCD 16x2 + PCF8574 | `0x27` | `0x3F` |
| OLED SSD1306 128x64 | `0x3C` | `0x3D` |

Si no sabes la dirección, sube este escáner:

```cpp
#include <Wire.h>

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Serial.println("Escaneando I2C...");
}

void loop() {
    for (uint8_t dir = 1; dir < 127; dir++) {
        Wire.beginTransmission(dir);
        if (Wire.endTransmission() == 0) {
            Serial.print("Encontrado en 0x");
            Serial.println(dir, HEX);
        }
    }
    delay(5000);
}
```

## Librerías

Instalar desde **Programa → Incluir librería → Administrar librerías**:

| Ejemplo | Librerías |
|---|---|
| `15_lcd_i2c` | `LiquidCrystal_I2C` (John Rickman) |
| `16_oled_i2c` | `Adafruit GFX Library` + `Adafruit SSD1306` |

No vienen con el IDE: sin instalarlas aparece error en el `#include`.

## Errores frecuentes

| Síntoma | Causa | Solución |
|---|---|---|
| LCD encendido sin texto | Contraste | Girar el potenciometro del módulo |
| OLED sin respuesta | Dirección distinta | Probar `0x3D` |
| Escáner no encuentra nada | SDA/SCL invertidos o cable suelto | Revisar conexiones |
| `No se encontro el OLED` | Igual que la fila anterior | Igual que la fila anterior |
| Pantalla con basura | Falta inicialización | Usar el sketch del ejemplo tal cual |

Guía completa, incluida la versión ESP32 y ESP-IDF: [`docs/06_pantallas_i2c.md`](../../Monitoria_ESP32_Intro_IE/docs/06_pantallas_i2c.md).
