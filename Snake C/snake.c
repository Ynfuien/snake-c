#include "snake.h"

extern int GRID_SIZE;

Snake* newSnake(int size) {
	Snake* s = malloc(sizeof(Snake));
	s->direciton = Right;
	List* bp = listCreate();

	s->headPixel = malloc(sizeof(Pixel));
	*s->headPixel = (Pixel){ GRID_SIZE / 2 + (size / 2), GRID_SIZE / 2 - 1 };
	for (int i = size - 1; i > 0; i--) {
		Pixel* body = malloc(sizeof(Pixel));
		*body = (Pixel){ s->headPixel->x - i, s->headPixel->y };
		listPush(bp, body);
	}

	s->bodyPixels = bp;
	return s;
}

void snakeRender(Snake* s, SDL_Renderer* r, SDL_Color headColor, SDL_Color bodyColor) {
	pixelRender(s->headPixel, r, headColor);

	Node* node = s->bodyPixels->head;
	while (node != NULL) {
		Pixel* p = (Pixel*)node->data;
		pixelRender(p, r, bodyColor);

		node = node->next;
	}
}

bool snakeMove(Snake* s, Border* border) {
	int x = s->headPixel->x;
	int y = s->headPixel->y;

	SnakeDirection dir = s->direciton;
	if (dir == Up) y--;
	else if (dir == Right) x++;
	else if (dir == Down) y++;
	else if (dir == Left) x--;


	Pixel* newHead = newPixel(x, y);
	if (snakeContains(s, newHead)) return false;
	if (borderContains(border, newHead)) return false;

	listPush(s->bodyPixels, s->headPixel);
	listShift(s->bodyPixels);
	s->headPixel = newHead;
	return true;
}

void snakeGrow(Snake* s) {
	Pixel* first = (Pixel*)listFirst(s->bodyPixels);
	Pixel* newBody = newPixel(first->x, first->y);
	listInsert(s->bodyPixels, newBody);
}

int snakeGetSize(Snake* s) {
	return s->bodyPixels->size + 1;
}

bool snakeContains(Snake* s, Pixel* pixel) {
	if (pixelEquals(s->headPixel, pixel)) return true;

	Node* node = s->bodyPixels->head;
	while (node != NULL) {
		Pixel* p = (Pixel*)node->data;
		if (pixelEquals(p, pixel)) return true;

		node = node->next;
	}

	return false;
}