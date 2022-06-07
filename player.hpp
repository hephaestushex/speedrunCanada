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

        Rectangle getRect()
        {
            // Rectangle me = {x - width / 2, y - height / 2, width, height};
            // return me;
            return Rectangle{x - width / 2, y - height / 2, width, height};
        }

        void draw()
        {
            if (e)
            {
                width+=100 * GetFrameTime();
            }
        
            if (x + width/2 >= GetScreenWidth())
            {
                x = GetScreenWidth() - width/2;
            }
            else if (x - width/2 <= 0)
            {
                x = 0 + width/2;
            }

            //std:: cout << x << std::endl; //Uncomment this to debug x

            
            DrawRectangleRec(getRect(), WHITE);
        }

	
};