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
