#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
/*
int madfgdgin(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    SDL_Texture* background = loadTexture("bikiniBottom.jpg", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);

    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    SDL_Texture* spongeBob = loadTexture("Spongebob.png", renderer);
    renderTexture(spongeBob, 200, 200, renderer);

    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    SDL_DestroyTexture( spongeBob );
    spongeBob = NULL;
    SDL_DestroyTexture( background );
    background = NULL;

    quitSDL(window, renderer);
    return 0;
}*/

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture("bikiniBottom.jpg");
    graphics.prepareScene(background);

    graphics.presentScene();
    waitUntilKeyPressed();

    SDL_Texture* spongeBob = graphics.loadTexture("Spongebob.png");
    graphics.renderTexture(spongeBob, 200, 200);

	graphics.presentScene();
	waitUntilKeyPressed();

	SDL_DestroyTexture( spongeBob );
    spongeBob = NULL;
    SDL_DestroyTexture( background );
    background = NULL;

    graphics.quit();
    return 0;
}
