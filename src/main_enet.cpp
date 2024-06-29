#include <enet/enet.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <iostream>
#include <string>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    if (enet_initialize() != 0) {
        std::cerr << "An error occurred while initializing ENet." << std::endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Variables
    bool isHosting = false;
    bool isJoining = false;
    bool isJoined = false;
    bool showTextInputBox = false;
    char gameID[64] = "\0";

    InitWindow(screenWidth, screenHeight, "Raylib ENet Client");
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetExitKey(KEY_Q); // Set the key to exit the game (default is ESC key

    // GUI: Initialize gui parameters
    GuiLoadStyle("/Users/ryan/code/projects/raylib-cmake-starter/vendor/raygui/styles/jungle/jungle.rgs");

    ENetHost* client = nullptr;
    ENetHost* server = nullptr;
    ENetPeer* peer = nullptr;
    ENetEvent event;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (isHosting && server) {
            ENetEvent event;
            while (enet_host_service(server, &event, 0) > 0) {
                std::cout << "Event type: " << event.type << std::endl;
                switch (event.type) {
                    case ENET_EVENT_TYPE_CONNECT:
                        std::cout << "A new client connected from " << event.peer->address.host << ":" << event.peer->address.port << std::endl;
                        // Assign the client a userData value to identify it in the future
                        event.peer->data = (void*)"Client information";
                        break;
                    case ENET_EVENT_TYPE_RECEIVE:
                        std::cout << "A packet of length " << event.packet->dataLength << " was received from " << event.peer->data
                                  << " on channel " << event.channelID << std::endl;
                        enet_packet_destroy(event.packet);
                        break;
                    case ENET_EVENT_TYPE_DISCONNECT:
                        std::cout << (char*)event.peer->data << " disconnected." << std::endl;
                        event.peer->data = NULL;
                        break;
                    default:
                        break;
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        if (GuiButton((Rectangle){ 25, 255, 125, 30 }, "Host")) {
            if (!isHosting && !isJoining) {
                ENetAddress address;
                enet_address_set_host(&address, "127.0.0.1");
                address.port = 1234;

                server = enet_host_create(&address, 1, 1, 0, 0);
                if (server == NULL) {
                    std::cerr << "An error occurred while trying to create an ENet server host." << std::endl;
                    isHosting = false;
                } else {
                    isHosting = true;
                    std::cout << "Hosting game..." << std::endl;
                }
            }
        }

        if (GuiButton((Rectangle){ 160, 255, 125, 30 }, "Join")) {
            if (!isHosting && !isJoining) {
                showTextInputBox = true;
            }
        }

        if (showTextInputBox) {
            // Add text box to input game ID
            int result = GuiTextInputBox((Rectangle){ (float)GetScreenWidth()/2 - 120, (float)GetScreenHeight()/2 - 60, 240, 140 }, "Join Game", "Enter Game ID", "Ok;Cancel", gameID, 64, NULL);

            if (result == 1) {
                // User clicked OK
                showTextInputBox = false;
                isJoining = true;
                client = enet_host_create(NULL, 1, 2, 0, 0);
                if (client == NULL) {
                    std::cerr << "An error occurred while trying to create an ENet client host." << std::endl;
                    isJoining = false;
                } else {
                    ENetAddress address;
                    enet_address_set_host(&address, "127.0.0.1");
                    address.port = 1234;
                    peer = enet_host_connect(client, &address, 1, 0);
                    if (peer == NULL) {
                        std::cerr << "No available peers for initiating an ENet connection." << std::endl;
                        isJoining = false;
                        isJoined = false;
                    } else {
                        isJoining = false;
                        isJoined = true;
                        std::cout << "Joining game with ID: " << gameID << std::endl;
                    }
                }
            } else if (result == 0 || result == 2) {
                // User clicked Cancel or closed the dialog
                showTextInputBox = false;
            }
        }

        if (isHosting) {
            DrawText("Hosting game...", 190, 200, 20, LIGHTGRAY);
        }

        if (isJoining) {
            DrawText("Joining game...", 190, 200, 20, LIGHTGRAY);
        }

        if(isJoined) {
            if(enet_host_service(client, &event, 5) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
                std::cout << "Connected to server." << std::endl;
                DrawText("Connected to server.", 190, 200, 20, LIGHTGRAY);
            }
        }

        EndDrawing();
    }

    // De-Initialization
    if (client) enet_host_destroy(client);
    if (server) enet_host_destroy(server);
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
