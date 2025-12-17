# Compiling 1942 Arcade Game to WebAssembly

This guide will help you compile your C++ game to run in a web browser using Emscripten.

## Prerequisites

### 1. Install Emscripten

**Windows:**

```bash
# Download and install using Git
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Install and activate the latest SDK
emsdk install latest
emsdk activate latest

# Set up environment variables for current session
emsdk_env.bat
```

**Linux/Mac:**

```bash
# Download and install using Git
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Install and activate the latest SDK
./emsdk install latest
./emsdk activate latest

# Set up environment variables for current session
source ./emsdk_env.sh
```

## Building for Web

### Using the build script (Recommended)

**Windows:**

```powershell
cd web
.\build.bat
```

**Linux/Mac:**

```bash
cd web
chmod +x build.sh
./build.sh
```

The build script will:

- Automatically collect all source files
- Compile with appropriate Emscripten flags
- Embed game resources
- Generate output files in `build-wasm/` directory

Output files:

- `game.html` - Main HTML file
- `game.js` - JavaScript glue code
- `game.wasm` - WebAssembly binary
- `game.data` - Embedded game resources

### Manual compilation (Alternative)

If you prefer to compile manually:

```bash
# From the project root directory
emcc src/*.cpp \
  -I includes \
  -o web/game.html \
  -s USE_SDL=2 \
  -s USE_SDL_IMAGE=2 \
  -s USE_SDL_MIXER=2 \
  -s SDL2_IMAGE_FORMATS='["png","bmp"]' \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s ASYNCIFY \
  --preload-file resources@/resources \
  --shell-file web/shell.html \
  -std=c++14
```

## Running the Game

### Method 1: Local Web Server (Recommended)

WebAssembly requires serving files over HTTP. Use Python's built-in server:

```bash
# Python 3
cd web/build-wasm
python -m http.server 8000

# Python 2
python -m SimpleHTTPServer 8000
```

Then open your browser to: `http://localhost:8000/1942-arcade-game-wasm.html`

### Method 2: Using Node.js http-server

```bash
# Install http-server globally
npm install -g http-servergame

# Navigate to the build directory
cd web/build-wasm

# Start the server
http-server -p 8000
```

### Method 3: Using emrun (Emscripten's built-in server)

```bash
cd web/build-wasm
emrun --port 8000 game.html
```

## Troubleshooting

### Common Issues:

1. **"SDL_Init failed"** - Make sure you're serving files over HTTP, not opening directly from filesystem

2. **Resources not loading** - Verify the `--preload-file` path is correct and resources directory exists

3. **Memory errors** - The game should use ALLOW_MEMORY_GROWTH, but if issues persist, you can set a fixed memory size:

   ```
   -s INITIAL_MEMORY=256MB
   ```

4. **Audio not working** - Web browsers require user interaction before playing audio. The game should handle this automatically.

## Optimization

For production builds, add optimization flags:

```bash
emcc src/*.cpp \
  -I includes \
  -o web/game.html \
  -s USE_SDL=2 \
  -s USE_SDL_IMAGE=2 \
  -s USE_SDL_MIXER=2 \
  -O3 \
  --closure 1 \
  -s ALLOW_MEMORY_GROWTH=1 \
  --preload-file resources@/resources \
  --shell-file web/shell.html
```

## Deployment

To deploy to a web server:

1. Upload these files to your web hosting:

   - `game.html`
   - `game.js`
   - `game.wasm`
   - `game.data`

2. Ensure your server sets correct MIME types:

   - `.wasm` → `application/wasm`
   - `.data` → `application/octet-stream`

3. For better performance, enable gzip compression on your server for `.js`, `.wasm`, and `.data` files.

## Browser Compatibility

The game should work on:

- Chrome/Edge 57+
- Firefox 52+
- Safari 11+
- Opera 44+

## Notes

- The initial load may take a few seconds as it downloads the game resources
- Audio may require user interaction (click) to start due to browser autoplay policies
- Save game functionality will use browser's IndexedDB storage
- Performance may vary compared to native builds depending on browser and hardware
