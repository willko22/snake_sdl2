#pragma once
#include "globals.hpp"
#include "renderManager.hpp"
#include "score.hpp"
#include "snake.hpp"
#include "food.hpp"
// #include "debugInfo.hpp"
// using namespace std;


class Game {
    private:
        SDL_Renderer* renderer;
        RenderManager renderManager;
        Score score;
        Snake snake;
        SDL_Rect foodBounds;
        std::vector<SDL_Rect> excludeRandPos;
        std::vector<Food> food;
        bool running = false, simulate = false;
        // DebugInfo debugInfo;
        unsigned int deltaTime, lastTime, currentTime;
        std::deque<Direction> keyBuffer;
        Direction beforeStop;
        SDL_Keycode key = SDLK_UNKNOWN;

        void handleEvents(SDL_Event& wEvent);
        void update();
        void render();
    public:
        Game(SDL_Renderer* renderer);
        ~Game();
        void run();
};