#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <assert.h>
#include <time.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "resource.h"
#include "assets.h"

#include "list.h"
#include "pixel.h"
#include "border.h"
#include "snake.h"
#include "berry.h"


void setupGame();
int setupWindow();
void render(SDL_Renderer* r);
void drawText(SDL_Renderer* r, char* text, int x, int y, SDL_Color color);
void tick();
void keyPressed(SDL_Scancode key);
long long getTimestamp();