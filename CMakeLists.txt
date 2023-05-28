cmake_minimum_required(VERSION 3.16)

project(raylib-starter)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(vendor/raylib)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add raylib include directory
target_include_directories(${PROJECT_NAME} PRIVATE vendor/raylib/src)

# Add raygui include directory
target_include_directories(${PROJECT_NAME} PRIVATE vendor/raygui/src)

# Raygui build command:
# gcc -o raygui.dynlib src/raygui.c -shared -fpic -DRAYGUI_IMPLEMENTATION -framework OpenGL -lm -lpthread -ldl $(pkg-config --libs --cflags raylib)

target_link_libraries(${PROJECT_NAME} raylib)
