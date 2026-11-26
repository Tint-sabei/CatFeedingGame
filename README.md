# Cat Feeding Game (SFML)

## How the game works
- Every 1.5 seconds all cats lose fullness (Fat Cats lose it twice as fast).
- Below 30 a cat is **hungry** (sad face, red bar, "I'm hungry!" and a meow). From 90 it is **sleepy** (full).
- Feeding adds +20 fullness (+30 for Fat Cats). Feeding a cat that would go over 100 is **overfeeding** ("Too full!!").
- Score: +10 for each feeding, -5 for overfeeding. Keep every cat fed!

## Controls
- Left / Right arrows or mouse click: choose a cat
- 1 = Fish, 2 = Dry food, 3 = Milk: feed the chosen cat
- S/s: the cat meows (also prints the ASCII cat in the console)
- N/n: add a new cat (max 6)
- Esc: quit

## Setup in VS Code
1. Install the VS Code extensions **C/C++** and **CMake Tools**.
2. Install a compiler + CMake + Git:
   - **Windows (MSYS2 UCRT64):** in the "MSYS2 UCRT64" terminal run `pacman -S mingw-w64-ucrt-x86_64-sfml`. Make sure `C:\msys64\ucrt64\bin` is in your Windows `PATH` (needed at runtime so Windows can find the SFML DLLs).
   - **Windows (Visual Studio Build Tools):** works with the automatic SFML download during CMake configure/build, nothing extra to install.
   - **macOS:** `xcode-select --install` and `brew install cmake`.
   - **Linux (Ubuntu):** `sudo apt install build-essential cmake git libx11-dev libxrandr-dev libudev-dev libgl1-mesa-dev libfreetype6-dev libopenal-dev libvorbis-dev libflac-dev`
3. Open this project folder in VS Code. When CMake Tools prompts for a kit, pick your compiler (for MSYS2 UCRT64, choose the **UCRT64** GCC kit—for example, `GCC ... ucrt64`—rather than a 32-bit or non-UCRT kit).
4. **Configure & Build:** Press **Build** on the bottom bar (or open the Command Palette with `Ctrl+Shift+P` / `Cmd+Shift+P` and run **CMake: Build**). If SFML is not installed on your system, the first build downloads and compiles it (a few minutes, needs internet).
5. **Run:** Click **Run** (the play button) or run **CMake: Run Without Debugging** from the Command Palette (`Ctrl+Shift+P` / `Cmd+Shift+P`). If you do not see the run/build buttons, open the **CMake** view in the sidebar, expand **Project Outline** → **CatFeedingGame**, and right-click `CatFeedingGame (Executable)` to build or run/debug.

### Fixing VS Code IntelliSense (`ASSET_DIR` or header squiggles)
Even when CMake builds the project fine, VS Code's C/C++ IntelliSense may show a red squiggle under `ASSET_DIR` or headers in `src/`:
1. Open the Command Palette (`Ctrl+Shift+P` / `Cmd+Shift+P`) and run **C/C++: Edit Configurations (UI)**.
2. Set **Compiler path** to your C++ compiler (for MSYS2 UCRT64: `C:/msys64/ucrt64/bin/g++.exe`).
3. Under **Include path**, add `${workspaceFolder}/src` (one path per line alongside `${default}`).
4. Under **Defines**, add `ASSET_DIR` pointing to your local `assets/` folder—for example:
   `ASSET_DIR="<path-to-project>/CatGame/assets/"`




