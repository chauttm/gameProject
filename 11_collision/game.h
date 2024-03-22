#ifndef GAME_H
#define GAME_H

#define INITIAL_SPEED 3
#define CHEESE_SIZE 10
#define MOUSE_SIZE 30

bool inside(int x, int y, SDL_Rect r) {
    return x > r.x && x < r.x+r.w && y > r.y && y < r.y+r.h;
}

bool overlap(const SDL_Rect& r1, const SDL_Rect& r2) {
    return inside(r1.x, r1.y, r2) || inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}

struct Cheese {
    SDL_Rect rect;
    Cheese(int x, int y) {
        rect.x = x;
        rect.y = y;
        rect.h = CHEESE_SIZE;
        rect.w = CHEESE_SIZE;
    }
};

struct Mouse {
    SDL_Rect rect;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;

    Mouse(int x, int y) {
        rect.x = x;
        rect.y = y;
        rect.h = MOUSE_SIZE;
        rect.w = MOUSE_SIZE;
    }

    bool canEat(const Cheese& cheese) {
        return overlap(rect, cheese.rect);
    }

    void grow() {
        rect.h += 2;
        rect.w += 2;
        speed += 1;
    }

    void move() {
        rect.x += dx;
        rect.y += dy;
    }
    void turnNorth() {
        dy = -speed;
        dx = 0;
    }
    void turnSouth() {
        dy = speed;
        dx = 0;
    }
    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }
};

void render(const Cheese& cheese, const Graphics& graphics) {
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 0, 255); // green
    SDL_RenderFillRect(graphics.renderer, &cheese.rect);
}

void render(const Mouse& mouse, const Graphics& graphics) {
    SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(graphics.renderer, &mouse.rect);
}

bool gameOver(const Mouse& mouse) {
    return mouse.rect.x < 0 || mouse.rect.x >= SCREEN_WIDTH ||
           mouse.rect.y < 0 || mouse.rect.y >= SCREEN_HEIGHT;
}

#endif // GAME_H
