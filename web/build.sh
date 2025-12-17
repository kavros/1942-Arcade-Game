#!/bin/bash

# Build script for 1942 Arcade Game WebAssembly version

echo "🎮 Building 1942 Arcade Game for WebAssembly..."

# Check if Emscripten is installed
if ! command -v emcc &> /dev/null; then
    echo "❌ Error: Emscripten is not installed or not in PATH"
    echo "Please install Emscripten first:"
    echo "  git clone https://github.com/emscripten-core/emsdk.git"
    echo "  cd emsdk"
    echo "  ./emsdk install latest"
    echo "  ./emsdk activate latest"
    echo "  source ./emsdk_env.sh"
    exit 1
fi

# Create build directory
echo "📁 Creating build directory..."
mkdir -p build-wasm
cd build-wasm

# Configure with CMake
echo "⚙️  Configuring with CMake..."
emcmake cmake .. || {
    echo "❌ CMake configuration failed"
    exit 1
}

# Build
echo "🔨 Building..."
emmake make || {
    echo "❌ Build failed"
    exit 1
}

echo "✅ Build completed successfully!"
echo ""
echo "📝 Output files:"
echo "  - 1942-arcade-game-wasm.html"
echo "  - 1942-arcade-game-wasm.js"
echo "  - 1942-arcade-game-wasm.wasm"
echo "  - 1942-arcade-game-wasm.data"
echo ""
echo "🚀 To run the game:"
echo "  cd build-wasm"
echo "  python -m http.server 8000"
echo "  Then open: http://localhost:8000/1942-arcade-game-wasm.html"
