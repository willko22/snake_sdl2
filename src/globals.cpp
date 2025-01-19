#include "../include/globals.hpp"

const char* WINDOW_TITLE = "Snake Game";
int TARGET_FPS = 7;
float TARGET_FRAME_DURATION = 1000 / TARGET_FPS - 1;
bool DEBUG_MOD = false;

//// Fonts
const char* FONT_PATH = "assets/fonts/Tiny5-Regular.ttf";
const char* DEBUG_FONT_PATH ="assets/fonts/Arial.ttf";
const int SCORE_FONT_SIZE = 40;
const int DEBUG_FONT_SIZE = 12;


//// Window and grid dimensions
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;
int TILE_SIZE = 20;
int GRID_TILES_COUNT_X = WINDOW_WIDTH / TILE_SIZE;
int GRID_TILES_COUNT_Y = WINDOW_HEIGHT / TILE_SIZE;
int GRID_WIDTH = GRID_TILES_COUNT_X * TILE_SIZE;
int GRID_HEIGHT = GRID_TILES_COUNT_Y * TILE_SIZE;
int MARGIN_X = (WINDOW_WIDTH - GRID_WIDTH) / 2;
int MARGIN_Y = (WINDOW_HEIGHT - GRID_HEIGHT) / 2;
int GRID_CENTER_TILE_X = GRID_TILES_COUNT_X / 2;
int GRID_CENTER_TILE_Y = GRID_TILES_COUNT_Y /2;

//// Game settings
int INITIAL_SNAKE_SIZE = 3;
int INITIAL_FOOD_AMOUNT = 1;
int APPLES_MODIFIER = 1;

//// Colors
SDL_Color BACKGROUND_COLOR = {0, 0, 0, 255};
SDL_Color APPLE_COLOR = {255, 0, 0, 255};
SDL_Color HEAD_COLOR = {255, 255, 255, 255};
SDL_Color BODY_COLOR = {200, 200, 200, 255};
SDL_Color TEXT_COLOR = {180, 180, 180, 200};
const SDL_Color DEBUG_TEXT_COLOR = {255, 255, 255, 255};


//// functions
void setRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

int getRandomNumber(int min, int max) {
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(min, max); // Define the range

    return distr(gen);
}
