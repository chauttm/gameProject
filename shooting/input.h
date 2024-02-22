#include <SDL.h>
#include "defs.h"
#include "structs.h"

struct Input {
    int keyboard[MAX_KEYBOARD_KEYS] = {0};

	void init()
    {
        for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) keyboard[i] = 0;
    }

    void get() {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    exit(0);
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyboard[event.key.keysym.scancode] = 1;
                    }
                    break;

                case SDL_KEYUP:
                    if (event.key.repeat == 0
                        && event.key.keysym.scancode < MAX_KEYBOARD_KEYS) {
                        keyboard[event.key.keysym.scancode] = 0;
                    }
                    break;

                default:
                    break;
            }
        }
    }
};
