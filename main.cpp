#include <iostream>
#include "raylib.h"
#include "include/player.hpp"
#include "include/objects.hpp"
#include "include/enemy.hpp"

bool play = false;
bool gameOver = false;
bool gameWon = false;
bool levelStart = true;
bool grounded = false;
bool jump = false;
bool spearFallen = false;

float gravity = 0;
float maxJumpHeight;
float level = 0;
float maxEnemies = level * 5;
float levelEnemyHits = level * 10;
float health = 3;
float spearTargetX;

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

    Player player(0, 0, 200, 32, 32, WHITE);
    Player spear(player.x, player.y, 0, 32, 32, BROWN);
    Object playButton(screenWidth / 4 - 64, screenHeight - screenHeight / 4 - 32, 128, 64, GREEN);
    Object exitButton(screenWidth - screenWidth / 4 - 64, screenHeight - screenHeight / 4 - 32, 128, 64, RED);
    Object ground(0, screenHeight - screenHeight / 4, screenWidth, screenHeight, GREEN);
    Object health1(screenWidth - 96, 0, 32, 32, RED);
    Object health2(screenWidth - 64, 0, 32, 32, RED);
    Object health3(screenWidth - 32, 0, 32, 32, RED);
    Enemy enemy1(screenWidth / 2 - 64, ground.y - 32, 100, 32, 32, levelEnemyHits);
    Enemy enemy2(screenWidth / 2 + 64, ground.y - 32, 100, 32, 32, levelEnemyHits);

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

                levelStart = true;
                gameOver = false;

                if (play) currentScreen = GAMEPLAY;
            } break;
            case GAMEPLAY:
            {
                framesCounter++;
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to BOSS screen
                
                if (gameOver)
                {
                    if (framesCounter % 300 == 0) currentScreen = TITLE;
                }
                
                if (levelStart)
                {
                    level++;
                    play = false;
                    health = 3;
                    float maxEnemies = level * 5;
                    float levelEnemyHits = level * 10;
                    enemy1.x = screenWidth / 2 - 64;
                    enemy1.y = ground.y - 32;
                    enemy2.x = screenWidth / 2 + 64;
                    enemy2.y = ground.y - 32;
                    player.x = ground.x;
                    player.y = ground.y - player.height;
                    grounded = false;
                    jump = false;
                    levelStart = false;
                    spearFallen = false; 
                }
            
                if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
                {
                    player.x -= player.speed * GetFrameTime();
                }

                if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
                {
                    player.x += player.speed * GetFrameTime();
                }

                if (IsKeyDown(KEY_SPACE) && !spearFallen)
                {
                    spear.speed = 200;
                    spear.x = player.x;
                    spear.y = ground.y - spear.height;
                    if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && !spearFallen)
                    { 
                        spearTargetX = spear.x += spear.speed;     
                    }
                    if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && !spearFallen)
                    {
                        spearTargetX = spear.x -= spear.speed;
                    }
                }

                if (spear.speed != 0 && !spearFallen)
                {
                    if (spearTargetX > spear.x && !spearFallen)
                    { 
                        spear.x += 10;
                        if (spearTargetX > spear.x) spearFallen = true;
                    }

                    if (spearTargetX < spear.x && !spearFallen)
                    {
                        spear.x -= 10;
                        if (spearTargetX > spear.x)
                        { spearFallen = true;
                    }
                }

                if (spear.x < 0 || spear.x > GetScreenWidth() - spear.width) spearFallen = true;

                if (!grounded) gravity += 10 * GetFrameTime();

                player.y += gravity;

                if (grounded) gravity = 0;

                if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && grounded) jump = true;

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

                
                if (player.x < enemy1.x && enemy1.x - player.x < 200 && player.y >= ground.y - maxJumpHeight / 2 - player.height) enemy1.x -= enemy1.speed * GetFrameTime();
                if (player.x > enemy1.x && player.x - enemy1.x < 200 && player.y >= ground.y - maxJumpHeight / 2 - player.height) enemy1.x += enemy1.speed * GetFrameTime();
                if (player.x < enemy2.x && enemy2.x - player.x < 200 && player.y >= ground.y - maxJumpHeight / 2 - player.height) enemy2.x -= enemy2.speed * GetFrameTime();
                if (player.x > enemy2.x && player.x - enemy2.x < 200 && player.y >= ground.y - maxJumpHeight / 2 - player.height) enemy2.x += enemy2.speed * GetFrameTime();
                if (enemy1.x < 0) enemy1.x = GetScreenWidth();
                if (enemy1.x > screenWidth) enemy1.x = 0;
                if (enemy2.x < 0) enemy2.x = GetScreenWidth();
                if (enemy2.x > screenWidth) enemy2.x = 0;

                if (CheckCollisionRecs(player.getRect(), enemy1.getRect()) || CheckCollisionRecs(player.getRect(), enemy2.getRect()))
                {
                    health--;
                    player.x = 0;
                    player.y = 0;
                    if (health < 1) gameOver = true;
                }

                if (CheckCollisionRecs(player.getRect(), spear.getRect()))
                {
                    spear.speed = 0;
                    spear.x = 0; spear.y = 0;
                    spearFallen = false;
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
                    playButton.draw();
                    exitButton.draw();
                    DrawText("speedrunCanada!", 20, 20, 40, BLACK);
                    DrawText("PLAY", playButton.x + playButton.width / 4, playButton.y + playButton.height / 4, 32, BLACK);
                    DrawText("EXIT", exitButton.x + exitButton.width / 4, exitButton.y + exitButton.height / 4, 32, BLACK);   
                } break;
                case GAMEPLAY:
                {
                    if (gameOver)
                    {
                        DrawText("Game Over", screenWidth / 2, screenHeight / 2, 64, BLACK);
                    }
                    else
                    {
                        DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                        ground.draw();
                        if (health == 3)
                        {
                            health1.draw();
                            health2.draw();
                            health3.draw();
                        }

                        else if (health == 2)
                        {
                            health2.draw();
                            health3.draw();
                        }

                        else health3.draw();
                        player.draw();
                        enemy1.draw();
                        enemy2.draw();

                        if (spear.speed != 0) spear.draw();
                    }
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
