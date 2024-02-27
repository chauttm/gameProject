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

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) cerr << " Up";
        if (currentKeyStates[SDL_SCANCODE_DOWN]) cerr << " Down";
        if (currentKeyStates[SDL_SCANCODE_LEFT]) cerr << " Left";
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) cerr << " Right";

        cerr << ".\n";

        SDL_Delay(100);
    }

    graphics.quit();
    return 0;
}

/*
//thử nghiệm scancode
int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_KEYDOWN:
                    cerr << "\nDown: " << event.key.keysym.scancode;
                    break;
                case SDL_KEYUP:
                    cerr << "\nUp: " << event.key.keysym.scancode;
                    break;
                default: cerr << "\n.";
            }
        }
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;
}
*/
