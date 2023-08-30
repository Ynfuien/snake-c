#include "berry.h"

extern int GRID_SIZE;

Berry* newBerry(Snake* snake) {
    Berry* b = malloc(sizeof(Berry));

    do {
        b->position = newPixel(randomInt(1, GRID_SIZE - 2), randomInt(1, GRID_SIZE - 2));
    } while (snakeContains(snake, b->position));


    return b;
}

void berryRender(Berry* b, SDL_Renderer* r, SDL_Color color) {
    pixelRender(b->position, r, color);
}

int randomInt(int min, int max) {
    return (rand() % max) + min;
}
