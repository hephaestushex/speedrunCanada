#include <iostream>
#include "raylib.h"
#include "include/buttons.hpp"
#include "include/player.hpp"

bool play = false;
bool gameOver = false;
bool gameWon = false;
//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

bool mouseClickInRange(float maxX, float minX, float maxY, float minY)
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() < maxX && GetMouseX() > minX && GetMouseY() < maxY && GetMouseY() > minY;
}

//------------------------------------------------------------------------------------------
// Main entry point
//------------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "speedrunCanada!");

    GameScreen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!

    Button playButton(screenWidth / 4, screenHeight - screenHeight / 4, 64, 32);
    Button exitButton(screenWidth - screenWidth / 4, screenHeight - screenHeight / 4, 64, 32);
    Player player(screenWidth, screenHeight, 200, 32, 32);

    int framesCounter = 0;          // Useful to count frames

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Game over handling logic code
        if (gameOver) break;

        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                if (mouseClickInRange(playButton.x + playButton.width, playButton.x, playButton.y + playButton.height, playButton.y)) play = true;
    
                if (mouseClickInRange(exitButton.x + exitButton.width, exitButton.x, exitButton.y + exitButton.height, exitButton.y)) gameOver = true;

                if (play) currentScreen = GAMEPLAY;
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                if (gameOver)
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLUE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    DrawText("made with raylib", 20, 20, 40, LIGHTGRAY);
                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawRectangleRec(playButton.getRect(), GREEN);
                    DrawRectangleRec(exitButton.getRect(), RED);
                    DrawText("speedrunCanada!", 20, 20, 40, BLACK);
                    DrawText("PLAY", playButton.x + 11, playButton.y + 8, 16, BLACK);
                    DrawText("EXIT", exitButton.x + 11, exitButton.y + 8, 16, BLACK);   
                } break;
                case GAMEPLAY:
                {
                    // TODO: Draw GAMEPLAY screen here!
                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
