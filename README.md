# Cycling Speed and Cadence Sensor Firmware

This firmware is for a custom NRF52810-based cycling speed and cadence sensor using ANT+ protocol.

http://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa700001


## 🔧 VS Code Debugging Setup for nRF5 SDK

### ✅ Step 1: Prerequisites

Make sure you have the following installed:

| Tool                                                                                                   | Purpose                    | Download |
| ------------------------------------------------------------------------------------------------------ | -------------------------- | -------- |
| [VS Code](https://code.visualstudio.com/)                                                              | Code editor                | ✅        |
| [nRF5 SDK](https://developer.nordicsemi.com/nRF5_SDK/)                                                 | Nordic SDK (e.g., v17.1.0) | ✅        |
| [GNU ARM Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-rm)                             | Build firmware             | ✅        |
| [nRF Command Line Tools](https://www.nordicsemi.com/Products/Development-tools/nRF-Command-Line-Tools) | Flash/debug with J-Link    | ✅        |
| [SEGGER J-Link Software](https://www.segger.com/downloads/jlink/)                                      | Debug adapter driver       | ✅        |
| [Cortex-Debug Extension](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)     | Debugging in VS Code       | ✅        |

---

## 🧩 Step 2: Connect the J-Link to Your PCB

| J-Link Pin | Connect To (nRF52810) |
| ---------- | --------------------- |
| SWDIO      | SWDIO                 |
| SWCLK      | SWDCLK                |
| GND        | GND                   |
| VTref      | VCC (1.8V–3.3V)       |

Then test your connection:

```bash
nrfjprog --recover      # Optional: erase everything
nrfjprog --reset        # Confirm communication
```

---

## 📂 Step 3: Create VS Code Project Structure

Assuming you have an nRF5 SDK project set up:

```
your_project/
├── config/                    # sdk_config.h, SoftDevice headers
├── src/                       # Your application .c files
├── main.c
├── Makefile
├── _build/                    # Output ELF and HEX files
├── .vscode/
│   ├── launch.json
│   └── tasks.json
```

---

## ⚙️ Step 4: Configure `.vscode/launch.json`

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "nRF52 Debug (J-Link)",
      "type": "cortex-debug",
      "request": "launch",
      "servertype": "jlink",
      "device": "nRF52810_xxAA",
      "interface": "swd",
      "runToEntryPoint": "main",
      "executable": "${workspaceFolder}/_build/firmware.elf",
      "cwd": "${workspaceFolder}",
      "svdFile": "${workspaceFolder}/nRF52810.svd"
    }
  ]
}
```

* Replace `firmware.elf` with your actual ELF file name.
* Optional: Download [nRF52810.svd](https://github.com/ARM-software/CMSIS_5/blob/develop/CMSIS/SVD/Nordic/nrf52810.svd) and place it in your root folder.

---

## 🛠️ Step 5: Add a Build Task (`tasks.json`)

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build Firmware",
      "type": "shell",
      "command": "make",
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

---

## 🚀 Step 6: Build, Flash, and Debug

### ▶️ **To Build:**

* Open command palette or `Terminal > Run Task > Build Firmware`
* Or press `Ctrl+Shift+B` to run the `make` command

### 🔥 **To Flash:**

```bash
nrfjprog --program _build/firmware.hex --sectorerase
nrfjprog --reset
```

Or use this as a custom task in `tasks.json`.

### 🐞 **To Debug:**

1. Set breakpoints in `main.c` or other files.
2. Press **F5** or click the **green run icon** in the Debug panel.
3. Step through your code, inspect variables, registers, and memory.

---

## 🔍 Optional Debugging Enhancements

### ✅ RTT Logging (instead of UART)

1. In `sdk_config.h`:

```c
#define NRF_LOG_BACKEND_RTT_ENABLED 1
#define NRF_LOG_BACKEND_UART_ENABLED 0
```

2. Add:

```c
#include "SEGGER_RTT.h"
SEGGER_RTT_WriteString(0, "Hello from RTT\n");
```

3. Monitor via terminal:

```bash
JLinkRTTViewerExe
# or
nrfjprog --reset
JLinkExe & JLinkRTTClient
```

---

## ✅ Troubleshooting Checklist

| Problem             | Fix                                                               |
| ------------------- | ----------------------------------------------------------------- |
| Can't connect       | Check power, SWD wiring, use `nrfjprog --recover`                 |
| Breakpoints ignored | Use `.elf`, not `.hex`; build with `-g` flag for debug symbols    |
| Flashing fails      | Make sure SoftDevice matches build, or erase chip before flashing |
| No logs             | Enable `NRF_LOG`, use RTT or UART                                 |
| Debug not starting  | Make sure `firmware.elf` path is correct in `launch.json`         |

---

Would you like me to generate a ready-to-use `.vscode` folder with example config for your specific setup?
