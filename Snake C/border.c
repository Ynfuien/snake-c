#include "border.h"


Border* newBorder(int size) {
	Border* b = malloc(sizeof(Border));
	List* l = listCreate();

	Pixel* ps;
	for (int i = 0; i <= size - 1; i++) {
		ps = malloc(sizeof(Pixel) * 4);

		// Border in width
		ps[0] = (Pixel){ i, 0 };
		ps[1] = (Pixel){ i, size - 1 };
		listPush(l, &ps[0]);
		listPush(l, &ps[1]);

		// Border in height
		if (i == 0 || i == size - 1) continue;
		ps[2] = (Pixel){ 0, i };
		ps[3] = (Pixel){ size - 1, i };
		listPush(l, &ps[2]);
		listPush(l, &ps[3]);
	}

	b->borderPixels = l;
	return b;
}

void borderRender(Border* b, SDL_Renderer* r, SDL_Color color) {
	Node* node = b->borderPixels->head;
	while (node != NULL) {
		Pixel* p = (Pixel*)node->data;
		pixelRender(p, r, color);

		node = node->next;
	}
}

bool borderContains(Border* b, Pixel* pixel) {
	Node* node = b->borderPixels->head;
	while (node != NULL) {
		Pixel* p = (Pixel*)node->data;
		if (pixelEquals(p, pixel)) return true;

		node = node->next;
	}

	return false;
}