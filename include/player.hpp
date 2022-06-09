#include <iostream>
#include "raylib.h"

class Player
{
	public:
        float x, y, speed, width, height;
        bool e;
        
	    Player(float pX, float pY, float pSpeed, float pWidth, float pHeight)
	    {
		    x = pX;
		    y = pY;
		    speed = pSpeed;
            width = pWidth;
            height = pHeight;
            e = false;
            
	    }

        Rectangle getRect(){return Rectangle{x, y, width, height};}

        void draw()
        {
            if (e)
            {
                width+=100 * GetFrameTime();
            }
            
            DrawRectangleRec(getRect(), WHITE);
        }	

};