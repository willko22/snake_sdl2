#include "../include/snake.hpp"

Snake::~Snake(){
    body.clear();
    bodySize = 0;
    growAmount = 0;
}

void Snake::move(){
    // body.push_front(head);
    int oldHeadX = head.x;
    int oldHeadY = head.y;

    moveHead();

    // cout << growAmount << endl;
    
    if (bodySize > 0 && growAmount == 0){
        std::rotate(body.begin(), std::prev(body.end()), body.end());
        body.front().x = oldHeadX;
        body.front().y = oldHeadY;
    } else if (growAmount > 0){
        body.push_front({oldHeadX, oldHeadY, head.w, head.h});
        bodySize++;
        growAmount--;
    } else while (growAmount < 0 && bodySize > 0){
        body.pop_back();
        bodySize--;
        growAmount++;
    }
    

    
    // if (growAmount < 0){
    //     while (growAmount < 0 && !body.empty()) {
    //         // deleteSegments.push_back(body.back());
    //         SDL_Rect lastSegment = body.back();

    //         growAmount++;
    //     }
    //     growAmount = 0;

    // }
    
    // if (growAmount > 0){
        
    //     body.push_back({oldHeadX, oldHeadY, head.w, head.h});
    //     bodyPtrs.push_front(&body.back());
        
    //     growAmount--;
        
    // } else if (growAmount == 0 && !body.empty()) {
    //     // Set the last segment to the position of the head
    //     SDL_Rect* lastSegmentPtr = bodyPtrs.back();
    //     lastSegmentPtr->x = oldHeadX;
    //     lastSegmentPtr->y = oldHeadY;

    //     bodyPtrs.pop_back();
    //     bodyPtrs.push_front(lastSegmentPtr);
    // }
}


void Snake::draw(SDL_Renderer* renderer){
    setRenderDrawColor(renderer, HEAD_COLOR);
    SDL_RenderFillRect(renderer, &head);

    if (!body.empty()){
        setRenderDrawColor(renderer, BODY_COLOR);
        for (SDL_Rect& segment : body){
            SDL_RenderFillRect(renderer, &segment);
        }
    }

    // if (!bodyPtrs.empty()){
    //     setRenderDrawColor(renderer, BODY_COLOR);
    //     for (SDL_Rect* segment : bodyPtrs){
    //         SDL_RenderFillRect(renderer, segment);
    //     }
    // }

    // if (growAmount == 0){
    //     setRenderDrawColor(renderer, BACKGROUND_COLOR);
    //     for (SDL_Rect& segment : deleteSegments){
    //         SDL_RenderFillRect(renderer, &segment);
    //     }
    //     deleteSegments.clear();
    //     deleteSegments.shrink_to_fit();
    // }
}

void Snake::reset(SDL_Rect initialHead){
    head = initialHead;
    body.clear();
    bodySize = INITIAL_SNAKE_SIZE;
    growAmount = INITIAL_SNAKE_SIZE;
    dir = STOP;
    indexOfLastSegment = 0;
    
}