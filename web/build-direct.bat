@echo off
REM Build script for 1942 Arcade Game WebAssembly version (Windows)

echo 🎮 Building 1942 Arcade Game for WebAssembly...

REM Check if Emscripten is installed
where emcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ❌ Error: Emscripten is not installed or not in PATH
    echo Please install Emscripten first:
    echo   git clone https://github.com/emscripten-core/emsdk.git
    echo   cd emsdk
    echo   .\emsdk install latest
    echo   .\emsdk activate latest
    echo   .\emsdk_env.bat
    exit /b 1
)

REM Create build directory
echo 📁 Creating build directory...
if not exist build-wasm mkdir build-wasm

REM Collect source files
echo 📝 Collecting source files...
set SRC_DIR=..\src
set INC_DIR=..\includes
set RES_DIR=..\resources

REM Build with emcc directly
echo 🔨 Compiling with Emscripten...
call emcc %SRC_DIR%\*.cpp ^
    -I %INC_DIR% ^
    -o build-wasm\game.html ^
    -std=c++14 ^
    -s USE_SDL=2 ^
    -s USE_SDL_IMAGE=2 ^
    -s USE_SDL_MIXER=2 ^
    -s SDL2_IMAGE_FORMATS="[\"png\",\"bmp\"]" ^
    -s ALLOW_MEMORY_GROWTH=1 ^
    -s ASYNCIFY ^
    --preload-file %RES_DIR%@/resources ^
    --shell-file shell.html

if %ERRORLEVEL% NEQ 0 (
    echo ❌ Build failed
    exit /b 1
)

echo ✅ Build completed successfully!
echo.
echo 📝 Output files:
echo   - game.html
echo   - game.js
echo   - game.wasm
echo   - game.data
echo.
echo 🚀 To run the game:
echo   cd build-wasm
echo   python -m http.server 8000
echo   Then open: http://localhost:8000/game.html

cd ..
