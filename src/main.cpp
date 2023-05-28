
#include "raylib.h"   

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Variables
    bool showTextInputBox = false;
    bool checked = false;

    InitWindow(screenWidth, screenHeight, "Raylib CMake Starter");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    //--------------------------------------------------------------------------------------

    // GUI: Initialize gui parameters
    // GuiLoadStyle("/Users/ryan/code/projects/raylib-cmake-starter/vendor/raygui/styles/cyber/cyber.rgs");
    GuiLoadStyle("/Users/ryan/code/projects/raylib-cmake-starter/vendor/raygui/styles/jungle/jungle.rgs");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if (GuiButton((Rectangle){ 25, 255, 125, 30 }, "Push me!")) {
            printf("Button clicked!\n");
        }

        // Add a checkbox
        GuiCheckBox((Rectangle){ 25, 290, 20, 20 }, "Check me", &checked);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
