# 📥 Instalación de Arduino IDE y primer programa

Guía paso a paso para dejar el entorno listo en **Windows, Linux y macOS**. Al final debes ver el LED de la placa parpadear cada segundo.

---

## 1. Descargar el IDE

Descarga **Arduino IDE 2.x** desde el sitio oficial:

<https://www.arduino.cc/en/software>

> ⚠️ Descarga siempre desde `arduino.cc`. Instaladores de blogs o "Arduino para PC full" suelen traer malware.

| Sistema | Archivo |
|---|---|
| Windows 10/11 | `arduino-ide_x.y.z_Windows_64bit.exe` |
| Linux x86_64 | `arduino-ide_x.y.z_Linux_64bit.AppImage` |
| macOS (Intel / Apple Silicon) | `.dmg` correspondiente |

---

## 2. Instalación por sistema operativo

### 🪟 Windows

1. Ejecuta el `.exe` y acepta la instalación (no requiere permisos de administrador si eliges "Install for me only").
2. Conecta la placa por USB.
3. Abre **Administrador de dispositivos** (`Win + X` → Administrador de dispositivos).
4. Revisa en **Puertos (COM y LPT)**:
   - `Arduino Uno (COMx)` → placa original, driver ya incluido.
   - `USB-SERIAL CH340 (COMx)` → clon con chip CH340.
   - ⚠️ `USB2.0-Serial` con signo amarillo → **falta el driver**.

**Driver CH340 (clones):** descárgalo del fabricante WCH (`CH341SER.EXE`), instálalo y reconecta la placa. Si sigue sin aparecer, prueba otro cable USB (muchos cables son solo de carga, sin datos).

### 🐧 Linux (Pop!_OS, Ubuntu, Debian, Arch)

El IDE se distribuye como **AppImage**:

```bash
chmod +x arduino-ide_*_Linux_64bit.AppImage
./arduino-ide_*_Linux_64bit.AppImage
```

Opcional: intégralo al menú de aplicaciones con AppImageLauncher o muévelo a `~/.local/bin/arduino-ide`.

**Permisos del puerto serie (obligatorio).** Sin esto el IDE no puede cargar programas:

```bash
sudo usermod -aG dialout $USER
```

Cierra sesión y vuelve a entrar (o reinicia) para que el grupo se aplique. Verifica con:

```bash
groups | grep dialout
```

**Regla udev para clones CH340** (si el puerto aparece y desaparece):

```bash
echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE="0666"' \
  | sudo tee /etc/udev/rules.d/99-ch340.rules
sudo udevadm control --reload-rules && sudo udevadm trigger
```

**Verificar que la placa es detectada:**

```bash
ls /dev/ttyACM* /dev/ttyUSB*    # ttyACM0 = original | ttyUSB0 = CH340
dmesg | tail -20                 # busca "FTDI", "CH341" o "cdc_acm"
```

Si usas `brltty` (lector de pantalla), desinstálalo: se apropia de `/dev/ttyACM0` y bloquea el puerto.

### 🍎 macOS

1. Abre el `.dmg` y arrastra Arduino IDE a **Aplicaciones**.
2. Al primer arranque: *Ajustes del Sistema → Privacidad y seguridad → Permitir*.
3. El puerto aparece como `/dev/cu.usbmodem...` (original) o `/dev/cu.usbserial-...` (CH340).
4. En clones CH340 instala el driver de WCH para macOS.

---

## 3. Configurar el IDE

1. Abre el IDE y ve a **Arduino IDE → Preferences** (o `Ctrl + ,`).
2. Idioma: **File → Preferences → Language → Español** (opcional).
3. Verifica que esté el core de AVR: **Tools → Board → Boards Manager** → busca `Arduino AVR Boards` → **Install**.
4. Selecciona la placa: **Tools → Board → Arduino AVR Boards → Arduino Uno**.
5. Selecciona el puerto: **Tools → Port → /dev/ttyACM0** (Linux/macOS) o **COM3** (Windows).

> El puerto solo aparece **con la placa conectada**. Si no está, el IDE muestra `Port: (no ports available)`.

---

## 4. Primer programa: Blink

1. **File → Examples → 01.Basics → Blink**.
2. Clic en **Verify (✓)** para compilar.
3. Clic en **Upload (→)** para cargar.
4. El LED marcado **L** en la placa debe parpadear cada segundo.

```
Compilando...         OK
Subiendo...           OK
```

Si el LED parpadea: **el entorno está listo**. 🎉

---

## 5. Errores comunes y solución

| Mensaje / síntoma | Causa | Solución |
|---|---|---|
| `Port: (no ports available)` | Cable sin datos, driver o placa | Cambia el cable, instala CH340, revisa `dmesg` |
| `avrdude: ser_open(): can't open device "/dev/ttyACM0": Permission denied` | Falta grupo `dialout` | `sudo usermod -aG dialout $USER` y reiniciar sesión |
| `avrdude: stk500_recv(): programmer is not responding` | Placa o puerto incorrecto | Verifica **Board = Arduino Uno** y el puerto correcto |
| `avrdude: stk500_getsync() attempt 1 of 10: not in sync` | Otro programa usa el puerto o la placa no es UNO | Cierra el Monitor Serial, confirma el modelo real de la placa |
| El puerto aparece y desaparece | CH340 sin regla udev / cable flojo | Aplica la regla udev, cambia cable |
| `brltty` toma el puerto en Linux | Servicio de accesibilidad | `sudo systemctl stop brltty-udev` o desinstalar |
| Compila pero no carga nada | Bootloader dañado (clon) | Graba bootloader con otro Arduino como ISP (avanzado) |
| La placa se calienta | Corto en el montaje | **Desconecta el USB de inmediato** y revisa conexiones |

---

## 6. Alternativas al IDE (opcional)

| Herramienta | Cuándo usarla |
|---|---|
| `arduino-cli` | Compilar y cargar desde terminal, scripts y CI |
| PlatformIO (VS Code) | Proyectos grandes, múltiples placas, control de versiones |
| Tinkercad Circuits | Simular sin hardware (útil si no tienes placa en casa) |

Ejemplo con `arduino-cli`:

```bash
arduino-cli core install arduino:avr
arduino-cli compile --fqbn arduino:avr:uno ejemplos/01_blink
arduino-cli upload  --fqbn arduino:avr:uno -p /dev/ttyACM0 ejemplos/01_blink
```

---

## ✅ Checklist de salida

- [ ] IDE instalado y abierto.
- [ ] Placa detectada en **Tools → Port**.
- [ ] **Board = Arduino Uno** seleccionado.
- [ ] Blink cargado y LED `L` parpadeando.
- [ ] Monitor Serial abre a **9600 baudios** sin errores.
