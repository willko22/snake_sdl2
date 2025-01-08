#pragma once
#include "globals.hpp"
#include "renderManager.hpp"
#include "score.hpp"
#include "snake.hpp"
#include "food.hpp"

using namespace std;


class Game {
    private:
        SDL_Renderer* renderer;
        RenderManager renderManager;
        Score score;
        Snake snake;
        Direction* currentDirection;
        SDL_Rect foodBounds;
        vector<Food> food;
        bool running;

        int lastTime;
        int currentTime;
        int deltaTime;

        void handleEvents(SDL_Event& wEvent);
        void update();
        void render();
    public:
        Game(SDL_Renderer* renderer);
        ~Game();
        void run();
};