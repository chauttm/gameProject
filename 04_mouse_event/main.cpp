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

    SDL_Rect rect;
    rect.x=100;
    rect.y=100;
    rect.h=100;
    rect.w=100;
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(graphics.renderer, &rect);
    SDL_RenderPresent(graphics.renderer);

    SDL_Event event;
    int x, y;
    while (true) {
        SDL_GetMouseState(&x, &y);
        //cerr << ((x > 100 && y > 100 && x < 200 && y < 200) ? "In\n" : "Out\n");

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 cerr << "Down at (" << x << ", " << y << ")\n";
                 break;
            case SDL_MOUSEBUTTONUP:
                 cerr << "Up at (" << x << ", " << y << ")\n";
                 break;
        }
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;
}
