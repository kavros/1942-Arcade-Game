cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_CXX_STANDARD 14)

project(1942-arcade-game-wasm VERSION "1.0.0" LANGUAGES C CXX)

# Set source file lists
file(GLOB SRC_FILES "../src/*.c" "../src/*.cpp")

# Set header file lists
file(GLOB HDR_FILES "../includes/*.h" "../includes/*.hpp")

# Add executable target
add_executable(
    ${PROJECT_NAME}
    ${HDR_FILES}
    ${SRC_FILES}
)

# Emscripten-specific settings
if(EMSCRIPTEN)
    # Use SDL2 ports in Emscripten
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_MIXER=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s SDL2_IMAGE_FORMATS='[\"png\",\"bmp\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ALLOW_MEMORY_GROWTH=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASYNCIFY")
    
    # Embed resources
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${CMAKE_SOURCE_DIR}/../resources@/resources")
    
    # Output settings
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "-s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_MIXER=2 -s ALLOW_MEMORY_GROWTH=1 -s ASYNCIFY --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/shell.html"
    )
    
    # Include directories
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../includes)
endif()
