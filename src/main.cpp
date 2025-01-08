#include "../include/globals.hpp"
#include "../include/game.hpp"

using namespace std;

int main( int argc, char *argv[] ){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        SDL_Log("TTF_Init error: %s\n", TTF_GetError());
        return 1;
    }
     
    SDL_Window* window =  SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        SDL_Log("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    cout << "WINDOW_WIDTH: " << WINDOW_WIDTH << endl;
    cout << "WINDOW_HEIGHT: " << WINDOW_HEIGHT << endl;
    cout << "TILE_SIZE: " << TILE_SIZE << endl;
    cout << "GRID_TILES_COUNT_X: " << GRID_TILES_COUNT_X << endl;
    cout << "GRID_TILES_COUNT_Y: " << GRID_TILES_COUNT_Y << endl;
    cout << "GRID_WIDTH: " << GRID_WIDTH << endl;
    cout << "GRID_HEIGHT: " << GRID_HEIGHT << endl;
    cout << "MARGIN_X: " << MARGIN_X << endl;
    cout << "MARGIN_Y: " << MARGIN_Y << endl;
    cout << "GRID_CENTER_TILE_X: " << GRID_CENTER_TILE_X << endl;
    cout << "GRID_CENTER_TILE_Y: " << GRID_CENTER_TILE_Y << endl;


    Game game(renderer);    
    game.run();

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}