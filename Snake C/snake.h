#ifndef SNAKE_H_
#define SNAKE_H_

#include <SDL2/SDL.h>
#include "list.h"
#include "pixel.h"
#include "border.h"

typedef enum SnakeDirection {
    Up,
    Right,
    Left,
    Down
} SnakeDirection;
typedef struct Snake {
    List* bodyPixels;
    Pixel* headPixel;
    SnakeDirection direciton;
} Snake;
Snake* newSnake(int size);
void snakeRender(Snake* s, SDL_Renderer* r, SDL_Color headColor, SDL_Color bodyColor);
bool snakeMove(Snake* s, Border* border);
void snakeGrow(Snake* s);
int snakeGetSize(Snake* s);
bool snakeContains(Snake* s, Pixel* pixel);

#endif
