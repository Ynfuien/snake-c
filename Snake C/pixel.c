#include "pixel.h"

extern int SCALE;

Pixel* newPixel(int x, int y) {
    Pixel* p = malloc(sizeof(Pixel));
    *p = (Pixel){ x, y };

    return p;
}

void pixelRender(Pixel* p, SDL_Renderer* r, SDL_Color c) {
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_Rect rect = { (p->x) * SCALE + (p->x), (p->y) * SCALE + (p->y), SCALE, SCALE };
    SDL_RenderFillRect(r, &rect);
}

bool pixelEquals(Pixel* p, Pixel* pixel) {
    return p->x == pixel->x && p->y == pixel->y;
}