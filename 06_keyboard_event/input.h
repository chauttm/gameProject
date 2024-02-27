#include <SDL.h>

#define MAX_KEYBOARD_KEYS 285

struct Input {
    bool keyDown[MAX_KEYBOARD_KEYS] = {false};
    bool quit = false;

    void get() {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyDown[event.key.keysym.scancode] = true;
                    }
                    break;

                case SDL_KEYUP:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyDown[event.key.keysym.scancode] = false;
                    }
                    break;

                default:
                    break;
            }
        }
    }
};
