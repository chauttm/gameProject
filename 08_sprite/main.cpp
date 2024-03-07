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

    Sprite man;
    SDL_Texture* manTexture = graphics.loadTexture(MAN_SPRITE_FILE);
    man.init(manTexture, MAN_FRAMES, MAN_CLIPS);

    Sprite bird;
    SDL_Texture* birdTexture = graphics.loadTexture(BIRD_SPRITE_FILE);
    bird.init(birdTexture, BIRD_FRAMES, BIRD_CLIPS);

    bool quit = false;
    SDL_Event e;
    while( !quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
        man.tick(); bird.tick();

        graphics.prepareScene();
        graphics.render(100, 100, man);
        graphics.render(150, 100, bird);
        graphics.presentScene();
        SDL_Delay(100);
    }

	SDL_DestroyTexture( manTexture ); manTexture = nullptr;
	SDL_DestroyTexture( birdTexture ); birdTexture = nullptr;

    graphics.quit();
    return 0;
}
