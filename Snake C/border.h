#ifndef BORDER_H_
#define BORDER_H_

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "list.h"
#include "pixel.h"


typedef struct Border {
    List* borderPixels;
} Border;
Border* newBorder(int size);
void borderRender(Border* b, SDL_Renderer* r, SDL_Color color);
bool borderContains(Border* b, Pixel* pixel);

#endif