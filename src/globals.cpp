#include "../include/globals.hpp"

using namespace std;

const char* WINDOW_TITLE = "Snake Game";
int TARGET_FPS = 8;
float TARGET_FRAME_DURATION = 1000 / TARGET_FPS;

//// Fonts
const char* FONT_PATH = "resource/fonts/Tiny5-Regular.ttf";
const int SCORE_FONT_SIZE = 40;

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
int INITIAL_SNAKE_SIZE = 1;
int INITIAL_FOOD_AMOUNT = 1;
int APPLES_MODIFIER = 1;

//// Colors
SDL_Color BACKGROUND_COLOR = {0, 0, 0, 255};
SDL_Color APPLE_COLOR = {255, 0, 0, 255};
SDL_Color HEAD_COLOR = {255, 255, 255, 255};
SDL_Color BODY_COLOR = {200, 200, 200, 255};
SDL_Color TEXT_COLOR = {180, 180, 180, 200};


//// functions
void setRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

int getRandomNumber(int min, int max, const set<int>& exclude) {
    random_device rd;  // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator
    uniform_int_distribution<> distr(min, max); // Define the range

    int randomNumber;
    do {
        randomNumber = distr(gen);
    } while (exclude.find(randomNumber) != exclude.end());

    return randomNumber;
}