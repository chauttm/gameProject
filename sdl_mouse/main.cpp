#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "input.h"
#include "logic.h"

#include <random>


using namespace std;


int main_f(int argc, char *argv[])
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,600); // distribution in range [1, 6]

    for (int i = 0; i < 100; i++) {
        int r =    dist6(rng);
        std::cout << r << "\t" << r % 2 << std::endl;
    }
}

int main(int argc, char *argv[]) {
    Graphics graphics;
    graphics.init();
    int x, y;

    SDL_Texture *targetterTexture = graphics.loadTexture("img/tinyBlackBox.png");

    while (1)
	{

	    SDL_GetMouseState(&x, &y);
	    cerr << x << ", " << y << endl;
	    SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;
            }
        }

        graphics.blit(targetterTexture, x, y, true);
        graphics.presentScene();
        SDL_Delay(100);
	}

    graphics.quit();
    return 0;
}


int mafgdfin(int argc, char *argv[])
{
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

        cerr << input.mouse.x << ", " << input.mouse.y << endl;

		game.doLogic(input);
        game.draw(graphics, input);

		graphics.presentScene();

		SDL_Delay(10);
	}

    graphics.quit();
    return 0;
}
