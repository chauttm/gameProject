#include <iostream>
#include <SDL.h>
#include "draw.h"

/*
move textures file name to graphic
change file name to match struct names
const
*/

using namespace std;

void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    long then = SDL_GetTicks();
	float remainder = 0;

    while (1)
	{
	    cerr << SDL_GetTicks() << endl;
        //SDL_Delay(rand()*10);
        capFrameRate(&then, &remainder);
	}

    graphics.quit();
    return 0;
}




