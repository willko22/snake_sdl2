#include "../include/snake.hpp"

Snake::Snake(SDL_Rect head)
    : head(head)
{
    headPtr = &head;
    dir = STOP;
}

Snake::~Snake(){
    body.clear();
    body.shrink_to_fit();

    // deleteSegments.clear();
    // deleteSegments.shrink_to_fit();
}

void Snake::move(){
    body.push_front(head);

    moveHead();

    if(growAmount == 0 && body.size() > 0){
        // deleteSegments.push_back(body.back());
        body.pop_back();
    } else if (growAmount < 0){
        while (growAmount < 0 && body.size() > 0) {
            // deleteSegments.push_back(body.back());
            body.pop_back();
            growAmount++;
        }
        growAmount = 0;

    } else {
        growAmount--;
    }
}


void Snake::draw(SDL_Renderer* renderer){
    setRenderDrawColor(renderer, HEAD_COLOR);
    SDL_RenderFillRect(renderer, headPtr);

    if (body.size() > 0){
        setRenderDrawColor(renderer, BODY_COLOR);
        for (SDL_Rect& segment : body){
            SDL_RenderFillRect(renderer, &segment);
        }
    }

    // if (growAmount == 0){
    //     setRenderDrawColor(renderer, BACKGROUND_COLOR);
    //     for (SDL_Rect& segment : deleteSegments){
    //         SDL_RenderFillRect(renderer, &segment);
    //     }
    //     deleteSegments.clear();
    //     deleteSegments.shrink_to_fit();
    // }
}
