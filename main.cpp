#include <iostream>
#include "raylib.h"
#include "include/buttons.hpp"
#include "include/player.hpp"
#include "include/objects.hpp"
#include "include/enemy.hpp"

bool play = false;
bool gameOver = false;
bool gameWon = false;
bool levelStart = true;
bool grounded = false;
bool jump = false;

float gravity = 0;
float maxJumpHeight;
float level = 0;
float maxEnemies = level * 5;
float levelEnemyHits = level * 10;
float health = 3;

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, BOSS} GameScreen;

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
    Player spear(player.x, player.y, 0, 32, 32);
    Object ground(0, screenHeight - screenHeight / 4, screenWidth, screenHeight);
    Object health1(screenWidth - 96, 0, 32, 32);
    Object health2(screenWidth - 64, 0, 32, 32);
    Object health3(screenWidth - 32, 0, 32, 32);
    Enemy enemy1(screenWidth / 2 - 64, ground.y - 32, 400, 32, 32, levelEnemyHits);
    Enemy enemy2(screenWidth / 2 + 64, ground.y - 32, 400, 32, 32, levelEnemyHits);

    maxJumpHeight = ground.y - player.height * 5 - player.height;

    //seed the pseudorand generator

    srand(time(0));

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

                // Press enter to change to BOSS screen
                if (gameOver)
                {
                    currentScreen = BOSS;
                }

                if (levelStart)
                {
                    level++;
                    float maxEnemies = level * 5;
                    float levelEnemyHits = level * 10;
                    player.x = ground.x;
                    player.y = ground.y - player.height;
                    grounded = false;
                    jump = false;
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



                if (!grounded) gravity += 10 * GetFrameTime();

                player.y += gravity;

                if (grounded) gravity = 0;

                if ((IsKeyDown(87) || IsKeyDown(KEY_UP)) && grounded) jump = true;

                if (player.y >= ground.y - player.height)
                {
                    player.y = ground.y - player.height;
                    grounded = true;
                }
                else grounded = false;

                if (player.y > maxJumpHeight && jump)player.y -= player.height / 4;

                if (player.y <= maxJumpHeight + 50) jump = false;

                if (player.x < 0) player.x = GetScreenWidth();

                if (player.x > screenWidth) player.x = 0;

                if (framesCounter % 30 == 0)
                {
                    if (player.x < enemy1.x && enemy1.x - player.x < 200) enemy1.x -= enemy1.speed * GetFrameTime();
                    if (player.x > enemy1.x && player.x - enemy1.x < 200) enemy1.x += enemy1.speed * GetFrameTime();
                }

            } break;
            case BOSS:
            {
                // TODO: Update BOSS screen variables here!

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
                    enemy1.draw();
                    enemy2.draw();
                } break;
                case BOSS:
                {
                    // TODO: Draw BOSS screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("BOSS SCREEN", 20, 20, 40, DARKBLUE);
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
