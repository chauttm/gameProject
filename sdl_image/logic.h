#ifndef _LOGIC__H
#define _LOGIC__H

#include <iostream>
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "draw.h"
#include "structs.h"

void initPlayer(Entity& player) {
    player.x = 100;
    player.y = 100;
    player.health = 1;
    player.side = SIDE_PLAYER;
    player.reload = 0;
}

void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
	int steps = max(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}

struct Game {
    Entity player;
    list<Entity*> bullets;
	list<Entity*> fighters;

    SDL_Texture *bulletTexture, *enemyTexture, *enemyBulletTexture;
    int enemySpawnTimer;
    int stageResetTimer;

    void reset()
    {
	    initPlayer(player);
        enemySpawnTimer = 0;
        stageResetTimer = FRAME_PER_SECOND * 2;
	}

    void init(Graphics& graphics)
    {
        player.texture = graphics.loadTexture("img/ship.png");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);
        fighters.push_back(&player);

        bulletTexture = graphics.loadTexture("img/tinyBlackBox.png");
        enemyTexture = graphics.loadTexture("img/enemy.png");
        enemyBulletTexture = graphics.loadTexture("img/enemyBullet.png");

        reset();
    }

    void fireBullet()
    {
        Entity *bullet = new Entity();
        bullets.push_back(bullet);

        bullet->x = player.x;
        bullet->y = player.y;
        bullet->y += (player.h / 2) - (bullet->h / 2);
        bullet->dx = PLAYER_BULLET_SPEED;
        bullet->health = 1;
        bullet->texture = bulletTexture;
        bullet->side = SIDE_PLAYER;
        SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

        player.reload = PLAYER_RELOAD;
    }

    void fireEnemyBullet(Entity* enemy)
    {
        Entity *bullet = new Entity();
        bullets.push_back(bullet);

        bullet->x = enemy->x;
        bullet->y = enemy->y;
        bullet->health = 1;
        bullet->texture = bulletTexture;
        bullet->side = SIDE_ALIEN;
        SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

        bullet->x += (enemy->w / 2) - (bullet->w / 2);
        bullet->y += (enemy->h / 2) - (bullet->h / 2);

        calcSlope(player.x + (player.w / 2), player.y + (player.h / 2),
                  enemy->x, enemy->y, &bullet->dx, &bullet->dy);
        bullet->dx *= ENEMY_BULLET_SPEED;
        bullet->dy *= ENEMY_BULLET_SPEED;

        enemy->reload = (rand() % FRAME_PER_SECOND * 2);
    }

    void doPlayer(int keyboard[])
    {
        if (player.health == 0) return;

        player.dx = player.dy = 0;

        if (player.reload > 0) player.reload--;
        if (keyboard[SDL_SCANCODE_UP]) player.dy = -PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_DOWN]) player.dy = PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_LEFT]) player.dx = -PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_RIGHT]) player.dx = PLAYER_SPEED;
        if (keyboard[SDL_SCANCODE_LCTRL] && player.reload == 0) fireBullet();
    }

    bool bulletHitFighter(Entity *b)
    {
        for (Entity* fighter: fighters) {
            if (fighter->side != b->side && b->collides(fighter)) {
                fighter->health = 0;
                return true;
            }
        }
        return false;
    }

    void doBullets(void)
    {
        auto it = bullets.begin();
        while (it != bullets.end()) {
            auto temp = it++;
            Entity* b = *temp;
            b->move();
            if (bulletHitFighter(b) || b->offScreen()) {
                delete b;
                bullets.erase(temp);
            }
        }
    }

    void doEnemies() {
        for (Entity* e: fighters) {
            if (e != &player && player.health != 0 && --e->reload <= 0)
                fireEnemyBullet(e);
        }
    }

    void spawnEnemies(void) {

        if (--enemySpawnTimer <= 0) {
            Entity *enemy = new Entity();
            fighters.push_back(enemy);
            enemy->x = SCREEN_WIDTH;
            enemy->y = rand() % SCREEN_HEIGHT;
            enemy->dx = -(2 + (rand() % 4));
            enemy->health = 1;
            enemy->reload = FRAME_PER_SECOND * (1 + (rand() % 3));
            enemy->side = SIDE_ALIEN;
            enemy->texture = enemyTexture;
            SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

            enemySpawnTimer = 30 + (rand() % 60);
        }
    }

    void doFighters(void)
    {
        auto it = fighters.begin();
        it++;

        while (it != fighters.end()) {
            auto temp = it++;
            Entity* fighter = *temp;

            fighter->move();
            if (fighter->x < -fighter->w) fighter->health = 0;

            if (fighter->health == 0) {
                delete fighter;
                fighters.erase(temp);
                continue;
            }
        }

        player.move();
        if (player.x < 0) player.x = 0;
        else if (player.x >= SCREEN_WIDTH - player.w)
            player.x = SCREEN_WIDTH - player.w;
        if (player.y < 0) player.y = 0;
        else if (player.y >= SCREEN_HEIGHT - player.h)
            player.y = SCREEN_HEIGHT - player.h;
	}

    void doLogic(int keyboard[]) {
        if (player.health == 0 && --stageResetTimer <= 0) reset();

        doPlayer(keyboard);
        doFighters();
        doEnemies();
        doBullets();
        spawnEnemies();
    }

    void draw(Graphics& graphics)
    {
		for (Entity* b: bullets)
            graphics.renderTexture(b->texture, b->x, b->y);

        for (Entity* b: fighters)
            if (b->health > 0)
                graphics.renderTexture(b->texture, b->x, b->y);
    }
};

#endif // _LOGIC__H
