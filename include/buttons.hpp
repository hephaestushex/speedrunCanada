#include "raylib.h"
#include <iostream>
#include <string>

class Button
{
    public:

    float x, y, width, height;

    Button(float bX, float bY, float bWidth, float bHeight)
    {
        x=bX;y=bY;width=bWidth;height=bHeight;
    }

    Rectangle getRect()
    {
        return Rectangle{x, y, width, height};
    }
};