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
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH ${ANGLE_LIBRARY_DIR}
    )
endif()


# Link against raylib libraries and ANGLE if using ANGLE
target_link_libraries(${PROJECT_NAME} raylib)
if (USE_ANGLE)
    target_link_libraries(${PROJECT_NAME} ${ANGLE_GLESv2_LIBRARY} ${ANGLE_EGL_LIBRARY})
endif()