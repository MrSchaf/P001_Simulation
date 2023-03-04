cmake_minimum_required(VERSION 3.24)
project(P001_Simulation C)

set(CMAKE_C_STANDARD 11)

set(SDL2_INCLUDE_DIR C:/temp/SDL/include)
set(SDL2_LIB_DIR C:/temp/SDL/lib/x64)
set(SDL2_IMAGE_INCLUDE_DIR C:/temp/SDL_IMAGE/include)
set(SDL2_IMAGE_LIB_DIR C:/temp/SDL_IMAGE/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(P001_Simulation main.c window.c window.h particles.c particles.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image)