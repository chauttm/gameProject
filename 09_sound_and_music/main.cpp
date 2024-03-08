#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"

using namespace std;

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Mix_Music *gMusic = graphics.loadMusic("assets\\RunningAway.mp3");
    graphics.play(gMusic);

    Mix_Chunk *gJump = graphics.loadSound("assets\\jump.wav");

    bool quit = false;
    SDL_Event event;
    while (!quit ) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) graphics.play(gJump);

        SDL_Delay(10);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk( gJump);

    graphics.quit();
    return 0;
}
