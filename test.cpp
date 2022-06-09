#include "raylib.h"
#include <iostream>
#include <map>

float y;
float gravity;

void setup()
{
	y = 10;
	gravity = 1;
}

int main()
{
    // starts a raylib window
    InitWindow(800, 600, "Pong");

    // limits FPS to moniters refresh rate.
    SetWindowState(FLAG_VSYNC_HINT);

    // sets up game variables
    setup();

	std::map<std::string, int> map1={{"w", 86}, {"a", 76}};

	std::cout << map1["w"] << std::endl;

    // game code
	while (!WindowShouldClose())
	{
		/** LOGIC **/
		gravity*=1.025;
		y += gravity;

		std::cout << "Gravity: " << gravity << " Y: " << y << "\n";

        	/** DRAWING **/
        	BeginDrawing();

        	ClearBackground(BLACK);

		DrawFPS(10, 10);

		DrawRectangle(GetScreenWidth() / 2 - 50, y, 100, 50, RAYWHITE);

        	EndDrawing();
	}

  	CloseWindow();

    return 0;
}
