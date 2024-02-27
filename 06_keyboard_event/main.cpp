#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "input.h"

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
    Input input;

    while (true) {
        input.get();
        if (input.quit) break;

        if (input.keyDown[SDL_SCANCODE_UP]) cerr << "Up\n";
        if (input.keyDown[SDL_SCANCODE_DOWN]) cerr << "Down\n";
        if (input.keyDown[SDL_SCANCODE_LEFT]) cerr << "Left\n";
        if (input.keyDown[SDL_SCANCODE_RIGHT]) cerr << "Right\n";
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;
}
