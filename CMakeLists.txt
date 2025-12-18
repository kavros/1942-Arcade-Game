cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_GENERATOR_PLATFORM x64)

project(1942-arcade-game VERSION "1.0.0" LANGUAGES C CXX)

# Set source file lists
file(GLOB SRC_FILES "src/*.c" "src/*.cpp")

# Set header file lists
file(GLOB HDR_FILES "includes/*.h" "includes/*.hpp")

# Set resource file lists
file(GLOB RESOURCE_FILES "resources/**/*")

configure_file (
    "${PROJECT_SOURCE_DIR}/includes/includes.h"
    "${PROJECT_BINARY_DIR}/includes.h"
)

# Add executable target
add_executable(
    ${PROJECT_NAME}
    ${HDR_FILES}
    ${SRC_FILES}
)

# Add SDL2 library
# Add SDL2 library
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${RAPIDJSON_INCLUDE_DIRS}
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM
)
