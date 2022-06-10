#include "raylib.h"
#include <iostream>
#include <string>

class Object
{
    public:

    float x, y, width, height;

    Color color;

    Object(float bX, float bY, float bWidth, float bHeight, Color bColor)
    {
        x = bX; y = bY; width = bWidth; height = bHeight; color = bColor;
    }

    Rectangle getRect()
    {
        return Rectangle{x, y, width, height};
    }

    void draw()
    {
        DrawRectangleRec(getRect(), color);
    }
};