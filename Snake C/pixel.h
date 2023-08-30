#ifndef PIXEL_H_
#define PIXEL_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct Pixel {
    int x;
    int y;
} Pixel;
Pixel* newPixel(int x, int y);
void pixelRender(Pixel* p, SDL_Renderer* r, SDL_Color c);
bool pixelEquals(Pixel* p, Pixel* pixel);


#endif