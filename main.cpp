#include <iostream>
#include "raylib.h"
#include "include/buttons.hpp"
#include "include/player.hpp"
#include "include/objects.hpp"

bool play = false;
bool gameOver = false;
bool gameWon = false;
bool levelStart = true;
bool falling = false;
bool jumping = false;

float gravity = 1.025;
float maxJumpHeight;
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

    Button playButton(screenWidth / 4 - 64, screenHeight - screenHeight / 4 - 32, 128, 64);
    Button exitButton(screenWidth - screenWidth / 4 - 64, screenHeight - screenHeight / 4 - 32, 128, 64);
    Player player(0, 0, 200, 32, 32);
    Object ground(0, screenHeight - screenHeight / 4, screenWidth, screenHeight);
    maxJumpHeight = player.height * 2 + ground.y;

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

                if (levelStart)
                {
                   player.x = ground.x;
                   player.y = ground.y - player.height;
                   levelStart = false; 
                }
            
                if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
                {
                    player.x -= player.speed * GetFrameTime();
                }

                if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
                {
                    player.x += player.speed * GetFrameTime();
                }

                if (player.y > maxJumpHeight)
                {
                    jumping = false;
                }
                
                if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
                {
                    if (player.y > maxJumpHeight)
                    {
                        player.y -= player.speed * GetFrameTime();
                        jumping = true;
                    }

                    else
                    {
                        jumping = false;
                    }
                }

                if (player.y < ground.y && !jumping)
                {
                    player.y = ground.y - player.height;
                    falling = false;
                }

                if (player.x < 0) player.x = 0;

                if (player.x > screenWidth) player.x = screenWidth;
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

            ClearBackground(RAYWHITE);

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
                    DrawText("PLAY", playButton.x + playButton.width / 4, playButton.y + playButton.height / 4, 32, BLACK);
                    DrawText("EXIT", exitButton.x + exitButton.width / 4, exitButton.y + exitButton.height / 4, 32, BLACK);   
                } break;
                case GAMEPLAY:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawRectangleRec(ground.getRect(), GREEN);
                    player.draw();
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
