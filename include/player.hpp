#include <iostream>
#include "raylib.h"

class Player
{
	public:
        float x, y, speed, width, height;
        Color color;
        bool e;
        
	    Player(float pX, float pY, float pSpeed, float pWidth, float pHeight, Color pColor)
	    {
		    x = pX;
		    y = pY;
		    speed = pSpeed;
            width = pWidth;
            height = pHeight;
            color = pColor;
            e = false;
	    }

        Rectangle getRect(){return Rectangle{x, y, width, height};}

        void draw()
        {
            if (e)
            {
                width+=100 * GetFrameTime();
            }
            
            DrawRectangleRec(getRect(), color);
        }	

};