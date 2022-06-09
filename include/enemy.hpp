#include <iostream>
#include "raylib.h"

class Enemy
{
	public:
        float x, y, speed, width, height, hits;
        bool e;
        
	    Enemy(float pX, float pY, float pSpeed, float pWidth, float pHeight, float pHits)
	    {
		    x = pX;
		    y = pY;
		    speed = pSpeed;
            width = pWidth;
            height = pHeight;
            hits = pHits;
            e = false;
            
	    }

        Rectangle getRect(){return Rectangle{x, y, width, height};}

        void draw()
        {
            if (e)
            {
                width+=100 * GetFrameTime();
            }
            
            DrawRectangleRec(getRect(), BLACK);
        }	

};