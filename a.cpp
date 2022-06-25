#include "raylib.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

std::map<std::string, int> map1 = { {"'", 39},
	{",", 44},
	{"-", 45},
	{".", 46},
	{"/", 47},
	{"0", 48},
	{"1", 49},
	{"2", 50},
	{"3", 51},
	{"4", 52},
	{"5", 53},
	{"6", 54},
	{"7", 55},
	{"8", 56},
	{"9", 57},
	{";", 59},
	{"=", 61},
	{"a", 65},
	{"b", 66},
	{"c", 67},
	{"d", 68},
	{"e", 69},
	{"f", 70},
	{"g", 71},
	{"h", 72},
	{"i", 73},
	{"j", 74},
	{"k", 75},
	{"l", 76},
	{"m", 77},
	{"n", 78},
	{"o", 79},
	{"p", 80},
	{"q", 81},
	{"r", 82},
	{"s", 83},
	{"t", 84},
	{"u", 85},
	{"v", 86},
	{"w", 87},
	{"x", 88},
	{"y", 89},
	{"z", 90},
	{"keypad 0", 320},
	{"keypad 1", 321},
	{"keypad 2", 322},
	{"keypad 3", 323},
	{"keypad 4", 324},
	{"keypad 5", 325},
	{"keypad 6", 326},
	{"keypad 7", 327},
	{"keypad 8", 328},
	{"keypad 9", 329},
	{"keypad .", 330},
	{"keypad /", 331},
	{"keypad *", 332},
	{"keypad -", 333},
	{"keypad +", 334},
	{"keypad enter", 335},
	{"keypad =", 336},
	{"[", 91},
	{"'\'", 92},
	{"]", 93},
	{"`", 96},
	{"space", 32},
	{"esc", 256},
	{"enter", 257},
	{"tab", 258},
	{"backspace", 259},
	{"ins", 260},
	{"del", 261},
	{"right", 262},
	{"left", 263},
	{"down", 264},
	{"up", 265},
	{"page up", 266},
	{"page down", 267},
	{"home", 268},
	{"end", 269}
};

std::string myText;
int jump, left, right, shoot;
int i = 0;
int increment;
float x, y, width, height;

int main () {
	// Read from the text file
	std::ifstream file("input.txt");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (file, myText)) {
  		// Output the text from the file
		if (i == 0) jump = map1[myText];
		if (i == 1) left = map1[myText];
		if (i == 2) right = map1[myText];
		if (i == 3) shoot = map1[myText];
		i++;
	}

	std::cout << jump << " " << left << " " << right << " " << shoot << "\n";

	// Close the file
	file.close();

	// starts a raylib window
    InitWindow(800, 600, "help me im dying");

    // limits FPS to moniters refresh rate.
    SetWindowState(FLAG_VSYNC_HINT);

	x = GetScreenWidth() / 2 - width / 2;
	y = GetScreenHeight() / 2 - height / 2;
	width = 100;
	height = width / 2;
	increment = 5;

    // game code
	while (!WindowShouldClose())
	{
		/** LOGIC **/
		if (IsKeyDown(jump) && y > 0) y -= increment;
		else if (IsKeyDown(left) && y + width / 2 < GetScreenHeight()) y += increment;
		if (IsKeyDown(right) && x>0) x-=increment;
		else if (IsKeyDown(shoot) && x + width < GetScreenWidth()) x += increment;

		/** DRAWING **/
		BeginDrawing();

		ClearBackground(BLACK);

		DrawFPS(10, 10);

		DrawRectangle(x, y, width, height, RAYWHITE);

		EndDrawing();
	}

  	CloseWindow();

	return 0;
}
