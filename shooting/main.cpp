#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "input.h"
#include "graphics.h"
#include "logic.h"
#include <ctime>

/*
move textures file name to graphic
change file name to match struct names
const
*/

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));

    Graphics graphics;
    graphics.init();

    Input input;
    input.init();
    Game game;
    game.init(graphics);

    while (1)
	{
		graphics.prepareScene();

		input.get();

		game.doLogic(input.keyboard);
        game.draw(graphics);

		graphics.presentScene();

		SDL_Delay(10);
	}

    graphics.quit();
    return 0;
}




