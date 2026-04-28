# Snake (SDL2)

A small Snake game using SDL2, written in C++.

**Features:**
- Simple snake gameplay
- Uses SDL2 for rendering and input
- Build targets for Debug and Release

**Prerequisites:**
- SDL2 development libraries and headers installed
- A POSIX-like build environment with `make` (MSYS2 / MinGW on Windows recommended)
- A C++ compiler (gcc/clang) supported by the makefile

**Build (from project root):**

```bash
# Debug build
make debug -j12

# Release build
make release -j16
```

**Run (examples):**

```bash
# Debug executable
build/debug/bin/main.exe

# Release executable
build/release/bin/main.exe
```

**Controls:**
- Arrow keys: move the snake
- Esc / Close window: quit

**Project layout (important paths):**
- `src/` — game source files (game loop, rendering, input)
- `include/` — headers (snake, game, render manager, etc.)
- `assets/` — fonts and other runtime assets
- `build/` — build outputs (debug/release bins and objs)

**Troubleshooting:**
- If the game fails to start because SDL2 DLLs are missing on Windows, ensure the SDL2 runtime DLLs are on your PATH or next to the executable (e.g., SDL2.dll, SDL2_ttf.dll if used).
- If compile errors reference missing headers, confirm SDL2 development headers are installed and your makefile points to the correct include/lib paths.

**Notes & Contributing:**
- This project is dedicated to the public domain under CC0 1.0 Universal. See LICENSE.
- Contributions: open an issue or submit a pull request. Keep changes small and focused.

Enjoy!
