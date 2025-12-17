# 1942 Arcade Game

## Overview

The project is a redevelopment of the original arcade game using the original sprite sheets.
Developed by Alexandro Kavroulaki, Niko Xenaki, Antonio Katsaraki for Game Development Course.

[![CMake](https://github.com/kavros/1942-Arcade-Game/actions/workflows/cmake.yml/badge.svg)](https://github.com/kavros/1942-Arcade-Game/actions/workflows/cmake.yml)

## Video

You can find a gameplay video in the following [link](https://www.youtube.com/watch?v=DqQoP_M39lQ)

## Prerequisites

- [CMake](https://cmake.org/)
- [vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell)
  - Follow the instructions to install vcpkg using PowerShell.
  - Ensure the `VCPKG_ROOT` environment variable is set.

## Build

Using **PowerShell**:

```powershell
# Install dependencies
vcpkg install

# Configure with vcpkg toolchain
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

# Build
cmake --build build --config Release --target ALL_BUILD -j 14
```

## Run

The game resources are copied to the build directory. To run the game, navigate to the executable's directory:

```powershell
cd build/Release
./1942-arcade-game.exe
```

## WebAssembly Build (Play in Browser)

You can compile the game to WebAssembly to run it in a web browser.

### 🌐 Play Online

**Live Demo:** The game is automatically deployed to GitHub Pages on every push!

Visit: `https://[your-username].github.io/1942-Arcade-Game/`

### Local Build Prerequisites

- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

### Install Emscripten

```powershell
# Clone the Emscripten SDK
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Install and activate the latest SDK
.\emsdk install latest
.\emsdk activate latest

# Activate PATH and other environment variables in the current terminal
.\emsdk_env.bat
```

### Build for Web

```powershell
# Navigate to the web directory
cd web

# Run the build script
.\build.bat
```

This will create:

- `build-wasm/game.html` - Main HTML file
- `build-wasm/game.js` - JavaScript glue code
- `build-wasm/game.wasm` - WebAssembly binary
- `build-wasm/game.data` - Embedded game resources

### Run in Browser

Start a local web server:

```powershell
cd build-wasm
python -m http.server 8000
```

Then open your browser to: `http://localhost:8000/game.html`

**Note:** WebAssembly files must be served over HTTP (not opened directly from the filesystem) due to browser security restrictions.

## GitHub Pages Deployment

The game automatically deploys to GitHub Pages via GitHub Actions. To set up:

1. **Enable GitHub Pages:**
   - Go to your repository Settings → Pages
   - Under "Source", select "GitHub Actions"
2. **Push your changes:**

   ```bash
   git add .
   git commit -m "Add WebAssembly build and GitHub Pages deployment"
   git push
   ```

3. **Wait for deployment:**
   - Check the Actions tab to see the build progress
   - Once complete, your game will be live at: `https://[your-username].github.io/1942-Arcade-Game/`

The deployment workflow automatically:

- Installs Emscripten
- Downloads dependencies (RapidJSON)
- Compiles the game to WebAssembly
- Deploys to GitHub Pages
