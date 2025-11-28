# CMake configuration for rlImGui library
# This file is stored outside the rlImGui submodule to avoid modifying vendor code

set(RLIMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/rlImGui)

# rlImGui sources
file(GLOB RLIMGUI_SOURCES
    "${RLIMGUI_DIR}/*.cpp"
)

# Create static library target
add_library(rlImGui STATIC ${RLIMGUI_SOURCES})

# Public include directory
target_include_directories(rlImGui PUBLIC ${RLIMGUI_DIR})

# rlImGui depends on raylib for rendering and input
target_link_libraries(rlImGui PUBLIC raylib)

# Link ImGui (should be defined before this point)
if (TARGET imgui)
    target_link_libraries(rlImGui PUBLIC imgui)
else()
    message(WARNING "rlImGui: Dear ImGui target 'imgui' not found. Build may fail.")
endif()
