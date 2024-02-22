#ifndef _INPUT__H

#define _INPUT__H

#include <SDL.h>
#include "defs.h"
#include "structs.h"

#define MAX_KEYBOARD_KEYS 350

struct Mouse {
    int x,y, wheel;
    bool leftButtonDown = false;
    bool rightButtonDown = false;

    void setMouseButtonDown(SDL_MouseButtonEvent event) {
        if (event.button == SDL_BUTTON_LEFT) leftButtonDown = true;
        else if (event.button == SDL_BUTTON_RIGHT) rightButtonDown = true;
    }

    void setMouseButtonUp(SDL_MouseButtonEvent event) {
        if (event.button == SDL_BUTTON_LEFT) leftButtonDown = false;
        else if (event.button == SDL_BUTTON_RIGHT) rightButtonDown = false;
    }
};

struct Input {
    int keyboard[MAX_KEYBOARD_KEYS] = {0};
    Mouse mouse;

	void init()
    {
        for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) keyboard[i] = 0;
    }

    void get() {
        SDL_GetMouseState(&mouse.x, &mouse.y);

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

                case SDL_MOUSEBUTTONDOWN:
                    mouse.setMouseButtonDown(event.button);
                    break;

                case SDL_MOUSEBUTTONUP:
                    mouse.setMouseButtonUp(event.button);
                    break;

                case SDL_MOUSEWHEEL:
                    mouse.wheel = event.wheel.y;
                    break;

                default:
                    break;
            }
        }
    }
};
#endif // _INPUT__H
