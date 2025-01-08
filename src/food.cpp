#include "../include/food.hpp"
Food::~Food(){
}

void Food::draw(SDL_Renderer* renderer){
    setRenderDrawColor(renderer, color);
    SDL_RenderFillRect(renderer, rectPtr);

}

void Food::setRandomPosition(){
    
    rect.x = randomBounds.x + (getRandomNumber(0, randomBounds.w / rect.w, {}) * rect.w);
    rect.y = randomBounds.y + (getRandomNumber(0, randomBounds.h / rect.h, {}) * rect.h);
}


