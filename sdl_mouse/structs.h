#ifndef _APP__H
#define _APP__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

using namespace std;

struct Entity {
	int x;
	int y;
	int w;
	int h;
    float dx;
	float dy;
	int health;
	int angle;
	SDL_Texture *texture;

	bool collides(Entity* other) {
	    return (max(x, other->x) < min(x + w, other->x + other->w))
	        && (max(y, other->y) < min(y + h, other->y + other->h));
	}

	void stayWithinBounds() {
	    x = min(max(x, w / 2), SCREEN_WIDTH - w / 2);
	    y = min(max(y, h / 2), SCREEN_HEIGHT - h / 2);
	}

	void move() {
	    x += dx;
	    y += dy;
	}

	bool offScreen() {
	     return x < -w || y < -h || x > SCREEN_WIDTH || y > SCREEN_HEIGHT;
	}
};

#endif // _APP__H
