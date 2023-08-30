#include "main.h"

// Undefine this def from Windows.h, so I can use this name in variable
#ifdef COLOR_BACKGROUND
#undef COLOR_BACKGROUND
#endif

// Configuration variables
const int GRID_SIZE = 32;
const int SNAKE_SIZE = 5;
const int SCALE = 20;
int RESOLUTION;
const int TICK_TIME = 100;

// Game colors
SDL_Color COLOR_BACKGROUND = { 36, 36, 36, 255 };
SDL_Color COLOR_SNAKEHEAD = { 10, 70, 128, 255 };
SDL_Color COLOR_SNAKEBODY = { 102, 154, 210, 255 };
SDL_Color COLOR_BERRY = { 255, 85, 85, 255 };
SDL_Color COLOR_BORDER = { 85, 85, 85, 255 };
SDL_Color COLOR_GAMEOVER = { 255, 85, 85, 255 };
SDL_Color COLOR_SCORE = { 255, 255, 85, 255 };
SDL_Color COLOR_SCORENUMBER = { 255, 170, 0, 255 };

// Game variables
Border* border;
Snake* snake;
Berry* berry;
SnakeDirection newDirection;
bool gameOver;

TTF_Font* font;


int main(int argc, char* argv[]) {
    setupGame();
    return setupWindow();
};


// Sets up game variables etc.
void setupGame() {
    srand(time(NULL));
    RESOLUTION = GRID_SIZE * SCALE + GRID_SIZE - 1;

    border = newBorder(GRID_SIZE);
    snake = newSnake(SNAKE_SIZE);
    berry = newBerry(snake);
    newDirection = snake->direciton;
    gameOver = false;
};

// Sets up graphic window and starts the game
int setupWindow() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred while initializing SDL", SDL_GetError(), NULL);
        return 1;
    }
    atexit(SDL_Quit);

    // Create window
    SDL_Window* window = SDL_CreateWindow("Snake C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RESOLUTION, RESOLUTION, SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred while creating window", SDL_GetError(), NULL);
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (!window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred while creating window renderer", SDL_GetError(), window);
        return 1;
    }


    // Initialize SDL TTF
    if (TTF_Init() != 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred while initializing SDL TTF", TTF_GetError(), window);
        return 1;
    }
    atexit(TTF_Quit);


    // Load font
    Asset* fontAsset = getAsset(ASSET_FILE_FONT, ASSET_TYPE_FONT);
    SDL_RWops* rw = SDL_RWFromMem(fontAsset->content, fontAsset->size);
    font = TTF_OpenFontRW(rw, 1, 16 * (SCALE / 10));
    if (!font) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred while loading font", TTF_GetError(), window);
        return 1;
    }

    // Game loop
    long long lastTick = getTimestamp();
    bool running = true;
    while (running) {
        // Window events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                keyPressed(event.key.keysym.scancode);
                break;
            }
        }

        if (gameOver) continue;

        // Check if it's time for the next tick
        long long now = getTimestamp();
        if (now - lastTick < TICK_TIME) continue;
        lastTick = now;

        // Tick and render the game
        tick();
        render(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
};


// Renderes everything
void render(SDL_Renderer* r) {
    // Clear
    SDL_Color c = COLOR_BACKGROUND;
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderClear(r);

    // Game over screen
    if (gameOver) {
        float scale = SCALE * 1.2;
        int score = snakeGetSize(snake) - SNAKE_SIZE;

        // Centered x position
        int x = RESOLUTION / 2;
        drawText(r, "Game over!", x, (int)(RESOLUTION / 2 - (scale * 2.3)), COLOR_GAMEOVER);

        // Create variable with "Score: {score}" string, get it's length and draw it
        char scoreNumberString[20];
        int lenght = snprintf(scoreNumberString, 20, "Score: %d", score);
        drawText(r, scoreNumberString, x, (int)(RESOLUTION / 2 - scale), COLOR_SCORENUMBER);

        // Create variable with "Score: {space times (score length in characters * 2)}" and draw it
        char scoreString[20];
        snprintf(scoreString, 20, "Score: %.*s", (lenght - 7) * 2, "          ");
        drawText(r, scoreString, x, (int)(RESOLUTION / 2 - scale), COLOR_SCORE);


        borderRender(border, r, COLOR_BORDER);
        SDL_RenderPresent(r);
        return;
    }

    // Render
    borderRender(border, r, COLOR_BORDER);
    snakeRender(snake, r, COLOR_SNAKEHEAD, COLOR_SNAKEBODY);
    berryRender(berry, r, COLOR_BERRY);

    SDL_RenderPresent(r);
};

// Draws centered text
void drawText(SDL_Renderer* r, char* text, int x, int y, SDL_Color color) {
    // Render text to a surface
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, color);

    // Create texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surface);


    // Render the texture on the renderer
    int width = surface->w;
    int height = surface->h;

    SDL_Rect rect = { x - (width / 2), y - (height / 2), width, height };
    SDL_RenderCopy(r, texture, NULL, &rect);

    // Free resources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
};


void tick() {
    snake->direciton = newDirection;

    // Move snake and check if it actually moved
    if (!snakeMove(snake, border)) {
        // Game over
        gameOver = true;
        return;
    }

    // Check if snake got the berry
    if (snakeContains(snake, berry->position)) {
        berry = newBerry(snake);
        snakeGrow(snake);
    }
};

// Handles pressed keys
void keyPressed(SDL_Scancode key) {
    if (gameOver) return;

    SnakeDirection dir = snake->direciton;
    switch (key) {
    case SDL_SCANCODE_UP:
    case SDL_SCANCODE_W:
        if (dir == Down) break;
        newDirection = Up;
        break;
    case SDL_SCANCODE_DOWN:
    case SDL_SCANCODE_S:
        if (dir == Up) break;
        newDirection = Down;
        break;
    case SDL_SCANCODE_LEFT:
    case SDL_SCANCODE_A:
        if (dir == Right) break;
        newDirection = Left;
        break;
    case SDL_SCANCODE_RIGHT:
    case SDL_SCANCODE_D:
        if (dir == Left) break;
        newDirection = Right;
        break;
    }
}


struct timespec ts;
long long getTimestamp() {
    timespec_get(&ts, TIME_UTC);
    return (long long)((ts.tv_sec * 1000) + (ts.tv_nsec / 1000000));
};