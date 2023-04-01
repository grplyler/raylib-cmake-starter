cmake_minimum_required(VERSION 3.16)

project(raylib-starter)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(vendor/raylib)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE vendor/raylib/src)
target_link_libraries(${PROJECT_NAME} raylib)
