#ifndef _LOGIC__H
#define _LOGIC__H

#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "structs.h"
#include "input.h"

struct Game {
    Entity player;
    list<Entity*> entities;

    SDL_Texture *targetterTexture;
    int stageResetTimer;

    void reset()
    {

	}

	void initPlayer(Graphics& graphics) {
	    entities.push_back(&player);
        player.texture = graphics.loadTexture("img/donk.png");
        player.health = 5;
        player.x = SCREEN_WIDTH / 2;
        player.y = SCREEN_HEIGHT / 2;

        SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);
    }

    void init(Graphics& graphics)
    {
        targetterTexture = graphics.loadTexture("img/tinyBlackBox.png");
        initPlayer(graphics);
    }

    float getAngle(int x1, int y1, int x2, int y2)
{
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}

    void doPlayer(Input& input) {
        player.dx *= 0.85;
        player.dy *= 0.85;

        if (input.keyboard[SDL_SCANCODE_W]) player.dy = -PLAYER_SPEED;
        if (input.keyboard[SDL_SCANCODE_S]) player.dy = PLAYER_SPEED;
        if (input.keyboard[SDL_SCANCODE_A]) player.dx = -PLAYER_SPEED;
        if (input.keyboard[SDL_SCANCODE_D]) player.dx = PLAYER_SPEED;
        player.angle = getAngle(player.x, player.y, input.mouse.x, input.mouse.y);
    }

    void doLogic(Input& input) {
        doPlayer(input);
        doEntities();
    }

    void doEntities() {
        for (Entity* e: entities) {
            e->move();
        }
        player.stayWithinBounds();
    }

    void draw(Graphics& graphics, Input& input)
    {
        graphics.blit(targetterTexture, input.mouse.x, input.mouse.y, true);

        for (Entity* e: entities) {
            graphics.blitRotated(e->texture, e->x, e->y, e->angle);
        }
    }
};

#endif // _LOGIC__H
