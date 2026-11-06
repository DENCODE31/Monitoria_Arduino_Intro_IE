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
   - `Silicon Labs CP210x USB to UART Bridge (COMx)` → clon con chip CP2102.
   - ⚠️ `USB2.0-Serial` con signo amarillo → **falta el driver**.

**Drivers CH340 y CP2102 (clones):** instálalos siguiendo la [sección 3](#3-drivers-del-chip-usb-uart-ch340-y-cp2102). Si sigue sin aparecer, prueba otro cable USB (muchos cables son solo de carga, sin datos).

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
ls /dev/ttyACM* /dev/ttyUSB*    # ttyACM0 = original | ttyUSB0 = CH340 o CP2102
dmesg | tail -20                 # busca "ch341", "cp210x" o "cdc_acm"
```

Si usas `brltty` (lector de pantalla), desinstálalo: se apropia de `/dev/ttyACM0` y bloquea el puerto.

### 🍎 macOS

1. Abre el `.dmg` y arrastra Arduino IDE a **Aplicaciones**.
2. Al primer arranque: *Ajustes del Sistema → Privacidad y seguridad → Permitir*.
3. El puerto aparece como `/dev/cu.usbmodem...` (original), `/dev/cu.usbserial-...` (CH340) o `/dev/cu.SLAB_USBtoUART` (CP2102).
4. En clones CH340 o CP2102, instala el driver del fabricante si no aparece el puerto (ver [sección 3](#3-drivers-del-chip-usb-uart-ch340-y-cp2102)).

---

## 3. Drivers del chip USB-UART (CH340 y CP2102)

> ⚠️ **Esta es la causa nº 1 de "mi placa no aparece".** Instala el driver *antes* de pelear con el IDE.

El computador no habla directo con el microcontrolador: entre el USB y el ATmega328P hay un **chip puente USB-UART**. Cada placa trae uno distinto y cada uno necesita su driver.

### 3.1 ¿Qué chip tiene mi placa?

| Chip | Dónde lo reconoces | Placas típicas |
|---|---|---|
| **ATmega16U2** | Chip cuadrado pequeño junto al conector USB-B | Arduino UNO original (no necesita driver aparte) |
| **CH340 / CH340G** | Chip rectangular con la inscripción `CH340` | Clones UNO / Nano económicos |
| **CP2102** (Silicon Labs) | Chip cuadrado pequeño con la inscripción `CP2102` o `CP210x` | Clones UNO, NodeMCU, ESP32 DevKit |

Si no logras leer el chip, conecta la placa y consulta el identificador USB (**VID:PID**):

| Chip | VID:PID | Nombre en Windows |
|---|---|---|
| CH340 | `1A86:7523` | `USB-SERIAL CH340 (COMx)` |
| CP2102 | `10C4:EA60` | `Silicon Labs CP210x USB to UART Bridge (COMx)` |

- **Windows:** Administrador de dispositivos → clic derecho en el dispositivo → *Propiedades → Detalles → Id. de hardware*.
- **Linux:** `lsusb` (busca `1a86:7523` o `10c4:ea60`).
- **macOS:** *Acerca de este Mac → Informe del sistema → USB*.

### 3.2 Instalar el driver

| Sistema | CH340 | CP2102 |
|---|---|---|
| 🪟 Windows | Descargar `CH341SER.EXE` de WCH (ver enlaces) y ejecutar **Install** | Descargar *CP210x Universal Windows Driver* de Silicon Labs, descomprimir y ejecutar el instalador (`CP210xVCPInstaller_x64.exe`) |
| 🐧 Linux | **No instalar nada**: el módulo `ch341` ya viene en el kernel | **No instalar nada**: el módulo `cp210x` ya viene en el kernel |
| 🍎 macOS | Driver de WCH solo si no aparece `/dev/cu.usbserial-*` | Driver de Silicon Labs solo si no aparece `/dev/cu.SLAB_USBtoUART` |

**Enlaces oficiales (descarga solo desde el fabricante):**

- CH340 (WCH), Windows: <https://www.wch-ic.com/downloads/CH341SER_EXE.html>
- CH340 (WCH), macOS: <https://www.wch-ic.com/downloads/CH341SER_MAC_ZIP.html>
- CH340 (WCH), Linux (solo si tu kernel no lo trae): <https://www.wch-ic.com/downloads/CH341SER_LINUX_ZIP.html>
- CP2102 (Silicon Labs), todos los sistemas: <https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers>

### 🪟 Windows: paso a paso

1. **Desconecta la placa** del USB.
2. Descarga e instala el driver que corresponde a tu chip (tabla anterior). Si Windows pide permisos de administrador, acéptalos.
3. En el instalador de WCH pulsa **INSTALL** y espera el mensaje `Driver install success`.
4. **Conecta la placa** (usa un cable con datos).
5. Abre el Administrador de dispositivos → **Puertos (COM y LPT)** y verifica que aparezca `USB-SERIAL CH340 (COMx)` o `Silicon Labs CP210x ... (COMx)` **sin signo amarillo**.
6. En el IDE: **Tools → Port → COMx**.

> En Windows 10/11 el driver a veces se instala solo al conectar la placa (Windows Update). Si aparece el COM sin signo amarillo, no hace falta instalar nada.

### 🐧 Linux: verificar que el driver cargó

```bash
lsusb                         # 1a86:7523 = CH340 | 10c4:ea60 = CP2102
lsmod | grep -E 'ch341|cp210x'
dmesg | tail -20              # "ch341-uart converter now attached to ttyUSB0"
ls /dev/ttyUSB* /dev/ttyACM*
```

Si el chip aparece en `lsusb` pero no hay `/dev/ttyUSB0`: revisa el grupo `dialout` (sección 2) y desinstala `brltty` (se apropia de los puertos CH340).

Regla udev para **CP2102** (equivalente a la de CH340 de la sección 2):

```bash
echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE="0666"' \
  | sudo tee /etc/udev/rules.d/99-cp2102.rules
sudo udevadm control --reload-rules && sudo udevadm trigger
```

### 🍎 macOS: verificar

```bash
ls /dev/cu.*
# CH340  -> /dev/cu.usbserial-XXXX  (o /dev/cu.wchusbserialXXXX con el driver de WCH)
# CP2102 -> /dev/cu.SLAB_USBtoUART
```

Si no aparece ningún puerto, instala el driver del fabricante, reinicia y autoriza la extensión en *Ajustes del Sistema → Privacidad y seguridad*.

### 3.3 Si sigue sin funcionar

| Síntoma | Qué hacer |
|---|---|
| El chip no aparece en ninguna parte (ni `lsusb` ni Administrador de dispositivos) | Cable solo de carga o puerto USB dañado: prueba otro cable y otro puerto |
| Signo amarillo en `USB2.0-Serial` / `Dispositivo desconocido` | Falta el driver: instálalo y reconecta |
| Aparece el COM pero falla la carga (`not in sync`) | Puerto equivocado o monitor serial abierto; confirma **Board = Arduino Uno** |
| Cambia el número de COM cada vez | Normal en Windows: vuelve a elegirlo en **Tools → Port** |
| Dos drivers de CH340 en conflicto (versiones viejas) | Desinstala el anterior desde *Aplicaciones y características* y reinstala el de WCH |

---

## 4. Configurar el IDE

1. Abre el IDE y ve a **Arduino IDE → Preferences** (o `Ctrl + ,`).
2. Idioma: **File → Preferences → Language → Español** (opcional).
3. Verifica que esté el core de AVR: **Tools → Board → Boards Manager** → busca `Arduino AVR Boards` → **Install**.
4. Selecciona la placa: **Tools → Board → Arduino AVR Boards → Arduino Uno**.
5. Selecciona el puerto: **Tools → Port → /dev/ttyACM0** (Linux/macOS) o **COM3** (Windows).

> El puerto solo aparece **con la placa conectada**. Si no está, el IDE muestra `Port: (no ports available)`.

---

## 5. Primer programa: Blink

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

## 6. Errores comunes y solución

| Mensaje / síntoma | Causa | Solución |
|---|---|---|
| `Port: (no ports available)` | Cable sin datos, driver o placa | Cambia el cable, instala el driver CH340 o CP2102 (sección 3), revisa `dmesg` |
| `avrdude: ser_open(): can't open device "/dev/ttyACM0": Permission denied` | Falta grupo `dialout` | `sudo usermod -aG dialout $USER` y reiniciar sesión |
| `avrdude: stk500_recv(): programmer is not responding` | Placa o puerto incorrecto | Verifica **Board = Arduino Uno** y el puerto correcto |
| `avrdude: stk500_getsync() attempt 1 of 10: not in sync` | Otro programa usa el puerto o la placa no es UNO | Cierra el Monitor Serial, confirma el modelo real de la placa |
| El puerto aparece y desaparece | CH340 sin regla udev / cable flojo | Aplica la regla udev, cambia cable |
| `brltty` toma el puerto en Linux | Servicio de accesibilidad | `sudo systemctl stop brltty-udev` o desinstalar |
| Compila pero no carga nada | Bootloader dañado (clon) | Graba bootloader con otro Arduino como ISP (avanzado) |
| La placa se calienta | Corto en el montaje | **Desconecta el USB de inmediato** y revisa conexiones |

---

## 7. Alternativas al IDE (opcional)

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
- [ ] Chip USB-UART identificado (ATmega16U2, CH340 o CP2102) y su driver instalado.
- [ ] Placa detectada en **Tools → Port**.
- [ ] **Board = Arduino Uno** seleccionado.
- [ ] Blink cargado y LED `L` parpadeando.
- [ ] Monitor Serial abre a **9600 baudios** sin errores.
