# CMake configuration for Dear ImGui library
# This file is stored outside the imgui submodule to avoid modifying vendor code

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/imgui)

# Core ImGui sources
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

# Create static library target
add_library(imgui STATIC ${IMGUI_SOURCES})

# Public include directory so other targets can find imgui.h
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

# Enable docking and viewports features
target_compile_definitions(imgui PUBLIC 
    IMGUI_ENABLE_DOCKING
    # IMGUI_ENABLE_VIEWPORTS  # Uncomment for multi-viewport support
)

# ImGui doesn't need any special compile options by default
# C++11 is sufficient
set_target_properties(imgui PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
