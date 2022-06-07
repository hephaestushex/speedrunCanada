#include "raylib.h"
#include <iostream>

class Object
{
    public:

    float x, y, width, height;

    Object(float bX, float bY, float bWidth, float bHeight)
    {
        x=bX;y=bY;width=bWidth;height=bHeight;
    }

    Rectangle getRect()
    {
        return Rectangle{x, y, width, height};
    }
};