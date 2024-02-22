#ifndef _LOGIC__H
#define _LOGIC__H

#include <iostream>
#include <list>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
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
    list<Entity*> explosions;
	list<Entity*> debris;

	Star stars[MAX_STARS];

    SDL_Texture *bulletTexture, *enemyTexture, *enemyBulletTexture, *background, *explosionTexture;
    int enemySpawnTimer;
    int stageResetTimer;

    int backgroundX = 0;

    void empty(list<Entity*>& entities) {
        while (!entities.empty()) {
            Entity* e = entities.front();
            entities.pop_front();
            if (e != &player) delete e;
        }
    }

    void initStarfield(void) {
        for (int i = 0 ; i < MAX_STARS ; i++)	{
            stars[i].x = rand() % SCREEN_WIDTH;
            stars[i].y = rand() % SCREEN_HEIGHT;
            stars[i].speed = 1 + rand() % 8;
        }
    }

    void reset()
    {
        empty(fighters);
        empty(bullets);
        empty(explosions);
        empty(debris);
        fighters.push_back(&player);
	    initPlayer(player);
	    initStarfield();
        enemySpawnTimer = 0;
        stageResetTimer = FRAME_PER_SECOND * 3;
	}

    void init(Graphics& graphics)
    {
        player.texture = graphics.loadTexture("img/ship.png");
        SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);

        bulletTexture = graphics.loadTexture("img/tinyBlackBox.png");
        enemyTexture = graphics.loadTexture("img/enemy.png");
        enemyBulletTexture = graphics.loadTexture("img/enemyBullet.png");
        background = graphics.loadTexture("img/bikiniBottom.jpg");
        explosionTexture = graphics.loadTexture("img/pngegg.png");

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

	void doBackground(void) {
        if (--backgroundX < -SCREEN_WIDTH)
        {
            backgroundX = 0;
        }
    }

    void doStarfield(void) {
        for (int i = 0 ; i < MAX_STARS ; i++) {
            stars[i].x -= stars[i].speed;

            if (stars[i].x < 0)
            {
                stars[i].x = SCREEN_WIDTH + stars[i].x;
            }
        }
    }

    void doExplosions(void) {
        auto it = explosions.begin();
        while (it != explosions.end()) {
            auto temp = it++;
            Entity* e = *temp;
            e->move();
            if (e->offScreen()) {
                delete e;
                explosions.erase(temp);
            }
        }
    }
/*
    void doDebris(void) {
        auto it = debris.begin();
        while (it != debris.end()) {
            auto temp = it++;
            Entity* e = *temp;
            e->move();
            e->dy += 0.5;
            if (--e->life <= 0) {
                delete e;
                debris.erase(temp);
            }
        }
    }
*/
    void doLogic(int keyboard[]) {
        doBackground();
        doStarfield();

        if (player.health == 0 && --stageResetTimer <= 0) reset();

        doPlayer(keyboard);
        doFighters();
        doEnemies();
        doBullets();
        spawnEnemies();

        doExplosions();
      //  doDebris();
    }

    void drawBackground(SDL_Renderer* renderer) {
        SDL_Rect dest;
        for (int x = backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH) {
            dest.x = x;
            dest.y = 0;
            dest.w = SCREEN_WIDTH;
            dest.h = SCREEN_HEIGHT;

            SDL_RenderCopy(renderer, background, NULL, &dest);
        }
    }

    void drawStarfield(SDL_Renderer* renderer) {
		for (int i = 0 ; i < MAX_STARS ; i++) {
            int c = 32 * stars[i].speed;
            SDL_SetRenderDrawColor(renderer, c, c, c, 255);
            SDL_RenderDrawLine(renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
        }
    }

    void draw(Graphics& graphics)
    {
        drawBackground(graphics.renderer);

        drawStarfield(graphics.renderer);

		for (Entity* b: bullets)
            graphics.renderTexture(b->texture, b->x, b->y);

        for (Entity* b: fighters)
            if (b->health > 0)
                graphics.renderTexture(b->texture, b->x, b->y);
    }
};

#endif // _LOGIC__H

