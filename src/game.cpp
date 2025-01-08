#include "../include/game.hpp"

using namespace std;

Game::Game(SDL_Renderer* inputRenderer) 
    : renderer(inputRenderer), 
    score("Score: ", {WINDOW_WIDTH/2, int(SCORE_FONT_SIZE*0.8), 110, 110}, CENTERED, TEXT_COLOR, FONT_PATH, SCORE_FONT_SIZE) ,
    snake({MARGIN_X + GRID_CENTER_TILE_X * TILE_SIZE, MARGIN_Y + GRID_CENTER_TILE_Y * TILE_SIZE, TILE_SIZE, TILE_SIZE}),
    running(false)
{
    
    renderManager.addRenderer(renderer);
    
    SDL_Rect* snakeHead = &snake.getHead();
    currentDirection = snake.getDirection();

    //// create apples
    int boundDistanceX = GRID_TILES_COUNT_X/3 * TILE_SIZE;
    int boundDistanceY = GRID_TILES_COUNT_Y/3 * TILE_SIZE;
    foodBounds = {
        snakeHead->y - boundDistanceX, 
        snakeHead->y - boundDistanceY, 
        snakeHead->x + boundDistanceX, 
        snakeHead->y + boundDistanceY
    };
    
    excludeRandPos.insert(snakeHead);
    for (int i = 0; i < INITIAL_FOOD_AMOUNT; i++){
        food.push_back(Food({0, 0, TILE_SIZE, TILE_SIZE}, APPLE_COLOR, APPLES_MODIFIER, foodBounds));
        food.back().setRandomPosition(excludeRandPos);
        excludeRandPos.insert(food.back().getRect());
    }

   
    for (Food& apple : food){
        renderManager.addElement(0, &apple);
    }
    renderManager.addElement(1, &snake);
    renderManager.addElement(2, &score);

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
        switch (wEvent.key.keysym.sym) {
            case SDLK_UP:
                if (*currentDirection != DOWN) snake.setDirection(UP);
                break;
            case SDLK_DOWN:
                if (*currentDirection != UP) snake.setDirection(DOWN);
                break;
            case SDLK_LEFT:
                if (*currentDirection != RIGHT) snake.setDirection(LEFT);
                break;
            case SDLK_RIGHT:
                if (*currentDirection != LEFT) snake.setDirection(RIGHT);
                break;
            case SDLK_ESCAPE:
                running = false;
                break;
            default:
                break;
        }
    }
}

void Game::update(){
    snake.move();
    if (snake.checkCollisionSelf()){
        running = false;
    }

    for (Food& apple : food){
        if (snake.checkCollision(apple.getRect())){
            int mod = apple.getModifier();
            score.incrementScore(mod);
            snake.grow(mod);

            deque<SDL_Rect*> excludeBodyPtrs = snake.getBody();
            for (SDL_Rect* excludeBodyPtr : excludeBodyPtrs){
                excludeRandPos.insert(excludeBodyPtr);
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
    unsigned int lastTime = SDL_GetTicks();
    unsigned int currentTime = SDL_GetTicks();
    unsigned int deltaTime = 0;

    running = true;
    while(running){

        while (SDL_PollEvent(&wEvent)) {
            handleEvents(wEvent);
        }

        lastTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime += currentTime - lastTime;
        if (deltaTime >= TARGET_FRAME_DURATION) {
            update();
            deltaTime -= TARGET_FRAME_DURATION;
        }

        render();
    }
}


