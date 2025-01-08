#include "../include/food.hpp"
Food::~Food(){
}

void Food::draw(SDL_Renderer* renderer){
    setRenderDrawColor(renderer, color);
    SDL_RenderFillRect(renderer, &rect);
}

void Food::setRandomPosition(set<SDL_Rect*> exclude){
    // make x and y sets out of rects
    set<int> xSet;
    set<int> ySet;
    for (SDL_Rect* exRect : exclude){
        //// from rectx to rect x+w
        for (int i = exRect->x; i < exRect->x + exRect->w; i++){ xSet.insert(i);}
        //// from recty to rect y+h
        for (int i = exRect->y; i < exRect->y + exRect->h; i++){ ySet.insert(i); }
    }

    rect.x = randomBounds.x + (getRandomNumber(0, randomBounds.w / rect.w, xSet) * rect.w);
    rect.y = randomBounds.y + (getRandomNumber(0, randomBounds.h / rect.h, ySet) * rect.h);
    // cout << "Food position: " << rect.x << ", " << rect.y << endl;
}


