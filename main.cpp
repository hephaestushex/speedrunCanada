#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "raylib.h"
#include "include/entities.hpp"
#include "include/objects.hpp"
#include "include/enemy.hpp"

bool play = false;
bool gameOver = false;
bool gameWon = false;
bool levelStart = true;
bool grounded = false;
bool jump = false;
bool spearFallen = false;
bool spearThrown = false;
bool leaveGame = false;
bool showControlsText = false;
bool showStoryText = false;
bool bossCutsceneOne = true;
bool bossCutsceneTwo = false;

float gravity = 0;
float maxJumpHeight;
float level = 0;
float maxEnemies = level * 5;
float levelEnemyHits = level * 10;
float health = 3;
float spearTargetX;
float spearDirection;
float bossHealth;
float playerHealthBossFight;

std::vector<std::string> dialogs;
std::vector<std::string> questions;
std::vector<int> dialogLeft;

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

    Entity player(0, 0, 200, 32, 32, WHITE);
    Entity spear(player.x, player.y, 0, 32, 32, BROWN);
    Object playButton(screenWidth / 4 - 64, screenHeight - screenHeight / 4 - 32, 128, 64, GREEN);
    Object exitButton(screenWidth - screenWidth / 4 - 64, screenHeight - screenHeight / 4 - 32, 128, 64, RED);
    Object controlsButton(screenWidth / 4 - 64, screenHeight / 4 - 32, 128, 64, YELLOW);
    Object storyButton(screenWidth - screenWidth / 4 - 64, screenHeight / 4 - 32, 128, 64, YELLOW);
    Object ground(0, screenHeight - screenHeight / 4, screenWidth, screenHeight, GREEN);
    Object health1(screenWidth - 160, 0, 32, 32, RED);
    Object health2(screenWidth - 96, 0, 32, 32, RED);
    Object health3(screenWidth - 32, 0, 32, 32, RED);
    Enemy enemy1(screenWidth / 2 - 64, ground.y - 32, 100, 32, 32, levelEnemyHits);
    Enemy enemy2(screenWidth / 2 + 64, ground.y - 32, 100, 32, 32, levelEnemyHits);

    maxJumpHeight = ground.y - player.height * 7 - player.height;

    std::ifstream dialog("dialog.txt");
    std::ifstream question("questions.txt");

    int index = 0;
    std::string temp;
    std::string playerTime;

    while (std::getline (dialog, temp)) {
  		// Output the text from the file
		dialogs.push_back(temp);
		index++;
	}

    while (std::getline (question, temp)) {
  		// Output the text from the file
		questions.push_back(temp);
		index++;
	}


    //seed the pseudorand generator

    srand(time(0));

    int framesCounter = 0;          // Useful to count frames
    int frameNumberToStop = 0;


    index = 10; //set value here for later use

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if (leaveGame) break;

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
    
                if (mouseClickInRange(exitButton.x + exitButton.width, exitButton.x, exitButton.y + exitButton.height, exitButton.y)) leaveGame = true;

                if (mouseClickInRange(storyButton.x + storyButton.width, storyButton.x, storyButton.y + storyButton.height, storyButton.y))
                {
                    showControlsText = false;
                    showStoryText = true;
                }

                if (mouseClickInRange(controlsButton.x + controlsButton.width, controlsButton.x, controlsButton.y + controlsButton.height, controlsButton.y))
                {
                    showStoryText = false;
                    showControlsText = true;
                }

                levelStart = true;
                level = 1;
                gameOver = false;

                if (play)
                {
                    currentScreen = GAMEPLAY;
                    framesCounter = 0;
                }
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
                    if (level == 1)
                    {
                        ground.color = DARKBLUE;
                    }
                    else if (level == 2)
                    {
                        ground.color = GOLD;
                    }
                    else if (level == 3)
                    { 
                        ground.color = WHITE;
                    }
                    else if (level == 4)
                    { 
                        ground.color = DARKGRAY;
                    }
                    play = false;
                    health = 3;
                    maxEnemies = level * 2 + 2;
                    levelEnemyHits = 3;
                    enemy1.x = screenWidth / 2 - 64;
                    enemy1.y = ground.y - 32;
                    enemy2.x = screenWidth / 2 + 64;
                    enemy2.y = ground.y - 32;
                    enemy1.hits = levelEnemyHits;
                    enemy2.hits = levelEnemyHits;
                    player.x = ground.x;
                    player.y = ground.y - player.height;
                    spear.x = 0;
                    spear.y = 0;
                    grounded = false;
                    jump = false;
                    levelStart = false;
                    spearFallen = false; 
                    spearDirection = 0;
                    spearTargetX = 0;
                    spearThrown = false;
                    spear.speed = 400;
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

                if (!spearThrown)
                {
                    spear.x = player.x;
                    spear.y = player.y;
                }

                if (IsKeyPressed(KEY_SPACE) && !spearThrown && grounded)
                {
                    spearDirection = 1;
                    spearTargetX = spear.x + spear.speed;
                    spearThrown = true;
                }

                if (IsKeyPressed(KEY_LEFT_SHIFT) && !spearThrown && grounded)
                {
                    spearDirection = -1;
                    spearTargetX = spear.x - spear.speed;
                    spearThrown = true;
                }

                if (spearThrown)
                {
                    if (spearDirection == 1) 
                    {
                        spear.x += spear.speed * GetFrameTime();
                        if (spear.x > spearTargetX)
                        {
                            spearFallen = true;
                        }
                    }
                    if (spearDirection == -1) 
                    {
                        spear.x -= spear.speed * GetFrameTime();
                        if (spear.x < spearTargetX)
                        {
                            spearFallen = true;
                        }
                    }
                }

                if (spear.x < 0 || spear.x + spear.width > screenWidth) spearFallen = true;

                if (spearFallen)
                {
                    spearTargetX = 0;
                    spearDirection = 0;
                }

                if (CheckCollisionRecs(player.getRect(), enemy1.getRect()) || CheckCollisionRecs(player.getRect(), enemy2.getRect()))
                {
                    health--;
                    player.x = 0;
                    player.y = 0;
                    if (health < 1) gameOver = true;
                }

                if (CheckCollisionRecs(player.getRect(), spear.getRect()) && spearFallen)
                {
                    spearThrown = false;
                    spearFallen = false;
                }

                if (CheckCollisionRecs(spear.getRect(), enemy1.getRect()) && !spearFallen && spearThrown)
                {
                    enemy1.hits--;
                    if (enemy1.hits == 0)
                    {
                        enemy1.x = 0;
                        enemy1.hits = levelEnemyHits;
                        maxEnemies--;
                    }
                    spearFallen = true;
                }

                if (CheckCollisionRecs(spear.getRect(), enemy2.getRect()) && !spearFallen && spearThrown)
                {
                    enemy2.hits--;
                    if (enemy2.hits == 0)
                    {
                        enemy2.x = 0;
                        enemy2.hits = levelEnemyHits;
                        maxEnemies--;
                    }
                    spearFallen = true;
                }

                if (maxEnemies < 0)
                {
                    level++;
                    if (level < 5) levelStart = true;
                    
                    else
                    {
                        currentScreen = BOSS;
                        level = 0;
                    }
                }

            } break;
            case BOSS:
            {
                framesCounter++;
                if (gameWon)
                {
                    if (framesCounter % 300 == 0) currentScreen = TITLE;
                }
                if (gameOver)
                {
                    if (framesCounter % 300 == 0) currentScreen = TITLE;
                }

                playerHealthBossFight = 10;
                bossHealth = 10;



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
                    controlsButton.draw();
                    storyButton.draw();
                    DrawText("speedrunCanada!", 20, 20, 40, BLACK);
                    DrawText("PLAY", playButton.x + playButton.width / 4, playButton.y + playButton.height / 4, 32, BLACK);
                    DrawText("EXIT", exitButton.x + exitButton.width / 4, exitButton.y + exitButton.height / 4, 32, BLACK);
                    DrawText("CONTROLS", controlsButton.x + controlsButton.width / 12, controlsButton.y + controlsButton.height / 3, 20, BLACK);
                    DrawText("STORY", storyButton.x + storyButton.width / 10, storyButton.y + storyButton.height / 4, 32, BLACK);
                    
                    if (showControlsText)
                    {
                        DrawText(dialogs[0].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6, 16, BLACK);
                        DrawText(dialogs[1].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 48, 16, BLACK);
                        DrawText(dialogs[2].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 96, 16, BLACK);
                        DrawText(dialogs[3].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 144, 16, BLACK);
                        DrawText(dialogs[4].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 192, 16, BLACK);
                    }

                    if (showStoryText)
                    {
                        DrawText(dialogs[5].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6, 16, BLACK);
                        DrawText(dialogs[6].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 48, 16, BLACK);
                        DrawText(dialogs[7].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 96, 16, BLACK);
                        DrawText(dialogs[8].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 144, 16, BLACK);
                        DrawText(dialogs[9].c_str(), screenWidth / 2 - screenWidth / 6, screenHeight / 2 - screenHeight / 6 + 192, 16, BLACK);
                    }

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

                        if (spearThrown)
                        {
                            spear.draw();
                        }
                    }
                } break;
                case BOSS:
                {
                    // TODO: Draw BOSS screen here!

                    if (gameWon)
                    {
                        DrawText("You Won!", screenWidth / 2, screenHeight / 2, 64, BLACK);
                        DrawText(playerTime.c_str(), screenWidth / 2, screenHeight / 2 - 128, 64, BLACK);    
                    }

                    else if (gameOver)
                    {
                        DrawText("GameOver", screenWidth / 2, screenHeight / 2, 64, BLACK);
                    }

                    else 
                    {
                        DrawRectangle(0, 0, screenWidth, screenHeight, BROWN);
                        
                        if (bossCutsceneOne)
                        {
                            DrawRectangle(screenWidth / 4, screenHeight / 2, 32, 32, BLACK);
                            DrawRectangle(screenWidth - screenWidth / 4, screenHeight / 2, 32, 32, player.color);
                            DrawText(dialogs[index].c_str(), screenWidth / 4 + 40, screenHeight / 2 + 64, 16, BLACK);
                            
                            if (framesCounter % 120 > 118)index++;

                            if (index == 17)
                            {
                                bossCutsceneOne = false;
                                index = 16;
                            }    
                        }

                        if (bossCutsceneTwo)
                        {
                            DrawRectangle(screenWidth / 4, screenHeight / 2, 32, 32, BLACK);
                            DrawRectangle(screenWidth - screenWidth / 4, screenHeight / 2, 32, 32, player.color);
                            DrawText(dialogs[index].c_str(), screenWidth / 4 + 40, screenHeight / 2 + 64, 16, BLACK);
                            
                            if (framesCounter % 120 > 118)index++;

                            if (index == 20)
                            {
                                bossCutsceneOne = true;
                                bossCutsceneTwo = false;
                                gameWon = true;
                                playerTime = "Time: " + std::to_string(framesCounter / 60); 
                                framesCounter = 0;
                                std::cout << playerTime << std::endl;
                            }
                        }

                        DrawRectangle(screenWidth / 4, screenHeight / 2, 32, 32, BLACK);
                        DrawRectangle(screenWidth - screenWidth / 4, screenHeight / 2, 32, 32, player.color);
                        
                        DrawRectangle(screenWidth / 4 - 64, (screenHeight / 4 - 32) - (bossHealth * 20), 32, bossHealth * 20, GREEN);
                        DrawRectangle((screenWidth - screenWidth / 4) + 64, screenHeight / 4 - 32 - (playerHealthBossFight * 20), 32, playerHealthBossFight * 20, GREEN);
                    }
                    
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
    dialog.close();
    //--------------------------------------------------------------------------------------

    return 0;
}
