#include "../include/game.hpp"
#include <thread>
#include <chrono>
// using namespace std;

Game::Game(SDL_Renderer* inputRenderer) 
    : renderer(inputRenderer), 
    score("Score: ", {WINDOW_WIDTH/2, int(SCORE_FONT_SIZE*0.8), 110, 110}, CENTERED, TEXT_COLOR, FONT_PATH, SCORE_FONT_SIZE) ,
    snake({MARGIN_X + GRID_CENTER_TILE_X * TILE_SIZE, MARGIN_Y + GRID_CENTER_TILE_Y * TILE_SIZE, TILE_SIZE, TILE_SIZE})
    , deltaTime(0)
{
    renderManager.addRenderer(renderer);
    
    SDL_Rect snakeHead = snake.getHead();
    snake.reset(snakeHead);
    // currentDirection = snake.getDirection();

    //// create apples
    // int boundDistanceX = GRID_TILES_COUNT_X;
    // int boundDistanceY = GRID_TILES_COUNT_Y;
    foodBounds = {
        0, 
        0, 
        GRID_TILES_COUNT_X-1,
        GRID_TILES_COUNT_Y-1
    };
    // cPrint(std::to_string(foodBounds.x) + " " + std::to_string(foodBounds.y) + " " + std::to_string(foodBounds.w) + " " + std::to_string(foodBounds.h));
    
    excludeRandPos.push_back(snakeHead);
    for (int i = 0; i < INITIAL_FOOD_AMOUNT; i++){
        food.push_back(Food({0, 0, TILE_SIZE, TILE_SIZE}, APPLE_COLOR, APPLES_MODIFIER, foodBounds));
        food.back().setRandomPosition(excludeRandPos);
        excludeRandPos.push_back(food.back().getRect());
    }

    
    for (Food& apple : food){
        renderManager.addElement(0, &apple);
    }
    renderManager.addElement(1, &snake);
    renderManager.addElement(2, &score);
    // renderManager.addElement(3, &debugInfo);

}

Game::~Game()
{
    renderManager.~RenderManager();
    score.~Score();
}

void Game::handleEvents(SDL_Event& wEvent){
    if (wEvent.type == SDL_QUIT) {
        running = false;
    }

    // Key press events
    if (wEvent.type == SDL_KEYDOWN) {
        key = wEvent.key.keysym.sym;

        if (key == SDLK_ESCAPE){
            running = false;
            return;
        }

        if (key == SDLK_SPACE){
            if (snake.getDirection() != STOP){
                beforeStop = snake.getDirection();
                snake.setDirection(STOP);
                keyBuffer.clear();
            } else if (snake.getDirection() == STOP){
                currentTime = SDL_GetTicks(); 
                snake.setDirection(beforeStop);
            }

            return;

        }

        if (keyBuffer.size() >= 3) return;
        switch (key){
            case SDLK_UP:
                if (!keyBuffer.empty()) { if(keyBuffer.back() != DOWN && keyBuffer.back() != UP) keyBuffer.push_back(UP); }
                else if (snake.getDirection() != DOWN) { keyBuffer.push_back(UP); }
                break;
            case SDLK_DOWN:
                if (!keyBuffer.empty()) { if(keyBuffer.back() != UP && keyBuffer.back() != DOWN) keyBuffer.push_back(DOWN); }
                else if (snake.getDirection() != UP) { keyBuffer.push_back(DOWN); }
                break;
            case SDLK_LEFT:
                if (!keyBuffer.empty()) { if(keyBuffer.back() != RIGHT && keyBuffer.back() != LEFT) keyBuffer.push_back(LEFT); }
                else if (snake.getDirection() != RIGHT) { keyBuffer.push_back(LEFT); }
                break;
            case SDLK_RIGHT:
                if (!keyBuffer.empty()) { if(keyBuffer.back() != LEFT && keyBuffer.back() != RIGHT) keyBuffer.push_back(RIGHT); }
                else if (snake.getDirection() != LEFT) { keyBuffer.push_back(RIGHT); }
                break;
            default:
                break;
        }
    
        if (snake.getDirection() == STOP && !keyBuffer.empty()){
            snake.setDirection(keyBuffer.front());
            keyBuffer.pop_front();
            currentTime = SDL_GetTicks(); 
        }

    }
}

void Game::update(){
    snake.move();
    
    // check out of bounds
    SDL_Rect head = snake.getHead();
    if (head.x < MARGIN_X || head.x >= MARGIN_X + GRID_WIDTH || head.y < MARGIN_Y || head.y >= MARGIN_Y + GRID_HEIGHT){
        running = false;
    }

    if (snake.checkCollisionSelf()){
        running = false;
    }

    for (Food& apple : food){
        SDL_Rect appleRect = apple.getRect();
        if (snake.checkCollision(&appleRect)){
            int mod = apple.getModifier();
            score.incrementScore(mod);
            snake.grow(mod);

            excludeRandPos.clear();
            std::list<SDL_Rect>* excludeBody = snake.getBody();
            for (SDL_Rect& bodyPtr : *excludeBody){
                excludeRandPos.push_back(bodyPtr);
            }
            excludeRandPos.push_back(snake.getHead());
            for (Food& apple : food){
                excludeRandPos.push_back(apple.getRect());
            }
            
            apple.setRandomPosition(excludeRandPos);
        }
    }

    
}

void Game::render(){
    setRenderDrawColor(renderer, BACKGROUND_COLOR);
    SDL_RenderClear(renderer);

    renderManager.drawAll();

    SDL_RenderPresent(renderer);
}

void Game::run()
{
    SDL_Event wEvent;

    running = true;
    while(running){

        while (SDL_PollEvent(&wEvent)) {
            handleEvents(wEvent);
        }

        if (snake.getDirection() != STOP){
            
            lastTime = currentTime;
            currentTime = SDL_GetTicks();
            deltaTime += currentTime - lastTime;
            if (deltaTime >= TARGET_FRAME_DURATION) {
                // debugInfo.updateCalcFPS(1000 / deltaTime); 

                if (!keyBuffer.empty()){
                    snake.setDirection(keyBuffer.front());
                    if (keyBuffer.size() > 1) keyBuffer.pop_front();
                }

                update();
                deltaTime -= TARGET_FRAME_DURATION;
            }
        }

        render();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}


