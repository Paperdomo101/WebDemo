# Raylib Web Demo

[![the demo](https://github.com/user-attachments/assets/fd86b7f3-2b4d-423e-8e5f-ee5f8ced497d)](#raylib-web-demo)

### Prerequisites

[Download WASM build of Raylib](https://github.com/raysan5/raylib/releases/download/5.0/raylib-5.0_webassembly.zip)

[Download and Install Emscripten](https://emscripten.org/docs/getting_started/downloads.html)

### Running the Demo

Open 'raylib-5.0_webassembly'. Copy `raylib.h` to ['include'](include) and `libraylib.a` to ['include/web'](include/web)

Set `EMSDK_PATH` and `BROWSER` in the [makefile](makefile)

Run `make test_web` and enjoy the demo

### Modifying the Demo

Change `PROJECT_NAME`, `PROJECT_VERSION`, `BASE_WIDTH`, `BASE_HEIGHT` in the [makefile](makefile)

Add build targets for other platforms in the [makefile](makefile) ([more info here](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation))

Customize the [embed shell](include/web/shell.html)

### itch.io Integration

Install [itch.io butler](https://itch.io/docs/butler). Create an [itch.io page](https://itch.io/game/new) for your game, set `ITCH_USER` and `ITCH_PAGE` in the [makefile](makefile)

Run `make release_web` to build and zip your game. Run `make publish_web` to upload directly to your itch.io page
