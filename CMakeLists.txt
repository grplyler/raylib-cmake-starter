cmake_minimum_required(VERSION 3.16)

project(raylib-starter)

set(CMAKE_CXX_STANDARD 14)

# Define ANGLE usage (must be before raylib subdirectory)
set(USE_ANGLE OFF)
if (USE_ANGLE)
    # Configure raylib to use OpenGL ES when using ANGLE
    set(OPENGL_VERSION "ES 2.0" CACHE STRING "OpenGL Version to build raylib with")
    set(GRAPHICS "GRAPHICS_API_OPENGL_ES2" CACHE STRING "Graphics API")
    
    # Define PLATFORM_DESKTOP_GLFW so raylib uses glad_gles2.h instead of system GLES2 headers
    add_definitions(-DPLATFORM_DESKTOP_GLFW)
else()
    # Configure raylib to use desktop OpenGL when not using ANGLE
    set(OPENGL_VERSION "3.3" CACHE STRING "OpenGL Version to build raylib with")
    set(GRAPHICS "GRAPHICS_API_OPENGL_33" CACHE STRING "Graphics API")
endif()

add_subdirectory(vendor/raylib)

# Include vendor libraries using external CMake files (not modifying submodules)
include(cmake/vendor/imgui.cmake)
include(cmake/vendor/rlImGui.cmake)

# Link required system frameworks for macOS
if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    # find_library(OPENGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    find_library(CORE_VIDEO_LIBRARY CoreVideo)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Main executable
add_executable(raylib-starter src/main.cpp)

# Add raylib include directory
target_include_directories(raylib-starter PRIVATE vendor/raylib/src)

# Add raygui include directory
target_include_directories(raylib-starter PRIVATE vendor/raygui/src)

# Add rglayout include directory
target_include_directories(raylib-starter PRIVATE vendor/rglayout/src)

# Link against raylib
target_link_libraries(raylib-starter PRIVATE raylib)

# Link rlImGui (if available)
target_include_directories(raylib-starter PRIVATE vendor/rlImGui)
target_link_libraries(raylib-starter PRIVATE rlImGui)

# Link macOS frameworks
if(APPLE)
    target_link_libraries(raylib-starter PRIVATE 
        ${COCOA_LIBRARY} 
        ${IOKIT_LIBRARY} 
        ${CORE_FOUNDATION_LIBRARY} 
        ${CORE_VIDEO_LIBRARY}
    )
endif()

# Configure ANGLE libraries if using ANGLE
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
    set_target_properties(raylib-starter PROPERTIES
        BUILD_RPATH ${ANGLE_LIBRARY_DIR}
    )
endif()

# Link against ANGLE if using ANGLE
if (USE_ANGLE)
    target_link_libraries(raylib-starter ${ANGLE_GLESv2_LIBRARY} ${ANGLE_EGL_LIBRARY})
endif()
