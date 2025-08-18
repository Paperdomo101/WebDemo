# Raylib Web Demo

[![banner](https://github.com/user-attachments/assets/92309fd2-6528-4592-af9c-46ffc463acff)](#raylib-web-demo)

---

## Prerequisites

[Download WASM build of Raylib](https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_webassembly.zip)

[Download and Install Emscripten](https://emscripten.org/docs/getting_started/downloads.html)

---

## Running the Demo

Open 'raylib-5.5_webassembly'. Copy `raylib.h` to ['include'](include) and `libraylib.a` to ['include/web'](include/web)

Set `EMSDK_PATH` and `BROWSER` in the [makefile](makefile)

Open a terminal at the project path, run `make` and enjoy the demo

---

## Modifying the Demo

Change `PROJECT_NAME`, `PROJECT_VERSION`, `BASE_WIDTH`, `BASE_HEIGHT` in the [makefile](makefile)

Add build targets for other platforms in the [makefile](makefile) ([more info here](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation))

Customize the [embed shell](include/web/shell.html)

---

## Integration with itch.io

Install [itch.io butler](https://itch.io/docs/butler). Create an [itch.io page](https://itch.io/game/new) for your game, set `ITCH_USER` and `ITCH_PAGE` in the [makefile](makefile)

Run `make release_web` to build and zip your game. Run `make publish_web` to upload directly to your itch.io page

---

## Changelog
### 18/08/2025

#### **[main.c](source/main.c)**
    + added `CalibrateScreen()` in favor of variable `recalculate_screen_resolution`
    * framerate is now calculated based on monitor refresh rate
    * reordered functions for improved readability (hopefully)
    * renamed `Init()` to `Load()`

#### **[makefile](makefile)**
    + added `clean` target
    * moved `test_web` target to top so `make` automatically executes it
    * changed default EMSDK_PATH to `~/Documents/emsdk`

#### **[shell.html](include/web/shell.html)**
    - removed superfluous things including C/JS interop function `saveFileFromMEMFSToDisk()`

#### **[README.md](README.md)**
    + added changelog
    * updated banner
    * updated formatting
