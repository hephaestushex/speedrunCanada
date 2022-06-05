#include "raylib.h"
#include <iostream>
#include <string>

class Button
{
    public:

    float x, y, width, height;
    const char *innerText;
    
    Button(float bX, float bY, float bWidth, float bHeight, const char *text)
    {
        innerText=nullptr;
        text = nullptr;
        x=bX;y=bY;width=bWidth;height=bHeight;innerText=text;
    }

    Rectangle getRect()
    {
        return Rectangle{x - width / 2, y - height / 2, width, height};
    }
};