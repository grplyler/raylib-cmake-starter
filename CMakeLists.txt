cmake_minimum_required(VERSION 3.16)

project(raylib-starter)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(vendor/raylib)
add_subdirectory(vendor/enet)

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Main executable
# add_executable(raylib-starter ${SOURCES})

# ENet executable
add_executable(raylib-starter-enet src/main_enet.cpp)

# Add raylib include directory
# target_include_directories(raylib-starter PRIVATE vendor/raylib/src)
target_include_directories(raylib-starter-enet PRIVATE vendor/raylib/src)

# Add raygui include directory
# target_include_directories(raylib-starter PRIVATE vendor/raygui/src)
target_include_directories(raylib-starter-enet PRIVATE vendor/raygui/src)

# Add enet include directory
target_include_directories(raylib-starter-enet PRIVATE vendor/enet/include)
include_directories(vendor/enet/include)

# Link against raylib  and enet
# target_link_libraries(raylib-starter raylib enet)
target_link_libraries(raylib-starter-enet raylib enet)

# Define path to ANGLE libraries if using ANGLE
set(USE_ANGLE OFF)
if (USE_ANGLE)
    set(ANGLE_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/libs")

    # Find ANGLE libraries
    find_library(ANGLE_GLESv2_LIBRARY libGLESv2.dylib PATHS ${ANGLE_LIBRARY_DIR})
    find_library(ANGLE_EGL_LIBRARY libEGL.dylib PATHS ${ANGLE_LIBRARY_DIR})

    # Check if the libraries were found
    if (NOT ANGLE_GLESv2_LIBRARY OR NOT ANGLE_EGL_LIBRARY)
        message(FATAL_ERROR "ANGLE libraries not found in ${ANGLE_LIBRARY_DIR}")
    endif()

    # Set runtime path for ANGLE libraries
    # set_target_properties(raylib-starter PROPERTIES
    #     BUILD_RPATH ${ANGLE_LIBRARY_DIR}
    # )
    set_target_properties(raylib-starter-enet PROPERTIES
        BUILD_RPATH ${ANGLE_LIBRARY_DIR}
    )
endif()

# Link against ANGLE if using ANGLE
if (USE_ANGLE)
    # target_link_libraries(raylib-starter ${ANGLE_GLESv2_LIBRARY} ${ANGLE_EGL_LIBRARY})
    target_link_libraries(raylib-starter-enet ${ANGLE_GLESv2_LIBRARY} ${ANGLE_EGL_LIBRARY})
endif()
