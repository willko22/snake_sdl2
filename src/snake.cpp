#include "../include/snake.hpp"

Snake::~Snake(){
    body.clear();
    body.shrink_to_fit();

    // deleteSegments.clear();
    // deleteSegments.shrink_to_fit();
}

void Snake::move(){
    // body.push_front(head);
    int oldHeadX = head.x;
    int oldHeadY = head.y;

    moveHead();

    if (growAmount < 0){
        while (growAmount < 0 && !body.empty()) {
            // deleteSegments.push_back(body.back());
            SDL_Rect* lastSegmentPtr = bodyPtrs.back();
            bodyPtrs.pop_back();

            auto it = find_if(body.begin(), body.end(), [lastSegmentPtr](const SDL_Rect& rect) {
                return &rect == lastSegmentPtr;
            });
            if (it != body.end()) {
                body.erase(it);
            }

            growAmount++;
        }
        growAmount = 0;

    }
    
    if (growAmount > 0){
        
        body.push_back({oldHeadX, oldHeadY, head.w, head.h});
        bodyPtrs.push_front(&body.back());
        
        growAmount--;
        
    } else if (growAmount == 0 && !body.empty()) {
        // Set the last segment to the position of the head
        SDL_Rect* lastSegmentPtr = bodyPtrs.back();
        lastSegmentPtr->x = oldHeadX;
        lastSegmentPtr->y = oldHeadY;

        bodyPtrs.pop_back();
        bodyPtrs.push_front(lastSegmentPtr);
    }
}


void Snake::draw(SDL_Renderer* renderer){
    setRenderDrawColor(renderer, HEAD_COLOR);
    SDL_RenderFillRect(renderer, &head);


    if (!bodyPtrs.empty()){
        setRenderDrawColor(renderer, BODY_COLOR);
        for (SDL_Rect* segment : bodyPtrs){
            SDL_RenderFillRect(renderer, segment);
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
