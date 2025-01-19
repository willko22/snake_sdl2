#include "../include/food.hpp"
Food::~Food(){
}

void Food::draw(SDL_Renderer* renderer){
    setRenderDrawColor(renderer, color);
    SDL_RenderFillRect(renderer, &rect);
}

void Food::setRandomPosition(const std::vector<SDL_Rect>& exclude){
    // make x and y sets out of rects

    int randX = 0;
    int randY = 0;

    bool found = false;
    while (!found){
        randX = getRandomNumber(randomBounds.x , randomBounds.w );
        randY = getRandomNumber(randomBounds.y , randomBounds.h );

        found = true;
        for (const SDL_Rect& excludeRect : exclude){
            if (!(randX + TILE_SIZE <= excludeRect.x || 
                    randX >= excludeRect.x + excludeRect.w || 
                    randY + TILE_SIZE <= excludeRect.y || 
                    randY >= excludeRect.y + excludeRect.h)) 
            {
                // cPrint("Food spawned wrong");
                found = false;
                break;
            }
        }
    }

    rect.x = randX * TILE_SIZE;
    rect.y = randY * TILE_SIZE;

}


