#pragma once
#include "SDL2/SDL_ttf.h" 
#include "SDL2/SDL.h"
#include <vector>
#include <deque>
#include <string> 
#include <random>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <cmath>
#include <set>

using namespace std;

extern const char* WINDOW_TITLE;
extern int TARGET_FPS;
extern float TARGET_FRAME_DURATION;

//// Fonts
extern const char* FONT_PATH;
extern const int SCORE_FONT_SIZE;

//// Window and grid dimensions
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int TILE_SIZE;
extern int GRID_TILES_COUNT_X;
extern int GRID_TILES_COUNT_Y;
extern int GRID_WIDTH;
extern int GRID_HEIGHT;
extern int MARGIN_X;
extern int MARGIN_Y;
extern int GRID_CENTER_TILE_X;
extern int GRID_CENTER_TILE_Y;

//// Colors
extern SDL_Color BACKGROUND_COLOR;
extern SDL_Color APPLE_COLOR;
extern SDL_Color HEAD_COLOR;
extern SDL_Color BODY_COLOR;
extern SDL_Color TEXT_COLOR;

//// Game settings
extern int INITIAL_SNAKE_SIZE;
extern int INITIAL_FOOD_AMOUNT;
extern int APPLES_MODIFIER;

//// Enums
enum Direction { UP, DOWN, LEFT, RIGHT, STOP};
enum TextMode { NORMAL, FIT, CENTERED, RATIO};

//// functions
extern void setRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& color);
extern int getRandomNumber(int min, int max, const set<int>& exclude);