cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_GENERATOR_PLATFORM x64)

project(1942-arcade-game VERSION "1.0.0" LANGUAGES C CXX)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2-2.0.16/")
set(SDL2_IMAGE_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2_image-2.0.5/")
set(SDL2_MIXER_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2_mixer-2.0.4/")

# Set source file lists
file(GLOB SRC_FILES "src/*.c" "src/*.cpp")

# Set header file lists
file(GLOB HDR_FILES "includes/*.h" "includes/*.hpp")

# Set resource file lists
file(GLOB RESOURCE_FILES "resources/**/*")

# Set lib file lists
file(GLOB LIB_FILES "${SDL2_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/*.dll" "${SDL2_IMAGE_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/*.dll" "${SDL2_MIXER_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/*.dll")

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
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add SDL2_image library
find_package(SDL2_IMAGE REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Add SDL2_mixer library
find_package(SDL2_MIXER REQUIRED)
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIB_FILES} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM
)
