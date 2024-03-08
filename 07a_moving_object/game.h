#ifndef GAME_H
#define GAME_H

#define INITIAL_SPEED 3

struct Mouse {
    int x, y;
    int dx = 0, dy = 0;
    int speed = INITIAL_SPEED;
    void move() {
        x += dx;
        y += dy;
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

void render(const Mouse& mouse, const Graphics& graphics) {
    SDL_Rect filled_rect;
    filled_rect.x = mouse.x;
    filled_rect.y = mouse.y;
    filled_rect.w = 10;
    filled_rect.h = 10;
    SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(graphics.renderer, &filled_rect);
}

bool gameOver(const Mouse& mouse) {
    return mouse.x < 0 || mouse.x >= SCREEN_WIDTH ||
           mouse.y < 0 || mouse.y >= SCREEN_HEIGHT;
}

#endif // GAME_H
