#ifndef BERRY_H_
#define BERRY_H_

#include <SDL2/SDL.h>
#include "pixel.h"
#include "snake.h"

typedef struct Berry {
    Pixel* position;
} Berry;
Berry* newBerry(Snake*);
void berryRender(Berry* b, SDL_Renderer* r, SDL_Color color);
int randomInt(int min, int max);

#endif
