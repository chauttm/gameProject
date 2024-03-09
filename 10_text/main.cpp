#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    TTF_Font* font = graphics.loadFont("assets/Purisa-BoldOblique.ttf", 100);

    SDL_Color color = {255, 255, 0, 0};
    SDL_Texture* helloText = graphics.renderText("Hello", font, color);

    graphics.renderTexture(helloText, 200, 200);

    graphics.presentScene();
    waitUntilKeyPressed();

	SDL_DestroyTexture( helloText );
    helloText = NULL;
    TTF_CloseFont( font );

    graphics.quit();
    return 0;
}
