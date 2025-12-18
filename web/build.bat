@echo off
REM Build script for 1942 Arcade Game WebAssembly version (Windows)

echo Building 1942 Arcade Game for WebAssembly...

REM Check if Emscripten is installed
where emcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo Error: Emscripten is not installed or not in PATH
    echo.
    echo Please run Command Prompt as Administrator and execute:
    echo   cd "C:\Program Files\emsdk"
    echo   emsdk_env.bat
    echo.
    echo Then run this build script again from a regular Command Prompt.
    echo.
    echo Alternative: Install emsdk in your user directory instead of Program Files
    exit /b 1
)

REM Create build directory
echo 📁 Creating build directory...
if not exist build-wasm mkdir build-wasm

REM Download RapidJSON if not present (header-only library)
if not exist "rapidjson" (
    echo Downloading RapidJSON...
    powershell -Command "& {Invoke-WebRequest -Uri 'https://github.com/Tencent/rapidjson/archive/refs/heads/master.zip' -OutFile 'rapidjson.zip'}"
    powershell -Command "& {Expand-Archive -Path 'rapidjson.zip' -DestinationPath '.' -Force}"
    move rapidjson-master rapidjson
    del rapidjson.zip
)

REM Collect source files
echo Collecting source files...
set SRC_DIR=..\src
set INC_DIR=..\includes
set RES_DIR=..\resources

REM Collect all cpp files dynamically
set CPP_FILES=
for %%f in (%SRC_DIR%\*.cpp) do call set CPP_FILES=%%CPP_FILES%% %%f

REM Build with emcc directly
echo 🔨 Compiling with Emscripten...
call emcc %CPP_FILES% ^
    -I %INC_DIR% ^
    -I rapidjson\include ^
    -DEMSCRIPTEN_BUILD ^
    -DNDEBUG ^
    -Wno-deprecated-declarations ^
    -o build-wasm\game.html ^
    -std=c++14 ^
    -s USE_SDL=2 ^
    -s USE_SDL_IMAGE=2 ^
    -s USE_SDL_MIXER=2 ^
    -s SDL2_IMAGE_FORMATS="[\"png\",\"bmp\"]" ^
    -s ALLOW_MEMORY_GROWTH=1 ^
    -s ASYNCIFY ^
    -s ASSERTIONS=0 ^
    --preload-file %RES_DIR%@/ ^
    --shell-file shell.html

if %ERRORLEVEL% NEQ 0 (
    echo Build failed
    exit /b 1
)

echo Build completed successfully!
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
