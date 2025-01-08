#pragma once    // Include guard
#include "globals.hpp"
#include "renderable.hpp"

class Snake : public Renderable {
    private:
        SDL_Rect head;
        // vector<SDL_Rect> deleteSegments;
        vector<SDL_Rect> body;
        deque<SDL_Rect*> bodyPtrs;
        int growAmount = 0;
        Direction dir;

        inline void moveHead();

    public:
        Snake(SDL_Rect initialHead) : head(initialHead), growAmount(0), dir(STOP){}
        ~Snake();
        void move();
        void draw(SDL_Renderer* renderer);

        inline void grow(int amount) { growAmount += amount; }
        inline bool checkCollision(SDL_Rect* other) const;
        inline bool checkCollisionSelf();
        inline void setDirection(Direction newDir) { dir = newDir; }
        inline SDL_Rect& getHead() { return head; }
        inline Direction* getDirection() { return &dir; }
        inline deque<SDL_Rect*>& getBody() { return bodyPtrs; }
};

inline bool Snake::checkCollision(SDL_Rect* other) const{
    return SDL_HasIntersection(&head, other);
}

inline bool Snake::checkCollisionSelf(){
    for (SDL_Rect& segment : body) {
        if (SDL_HasIntersection(&head, &segment)) {
            return true;
        }
    }
    return false;
}

inline void Snake::moveHead(){
    switch(dir){
        case UP: head.y -= TILE_SIZE; break;
        case DOWN: head.y += TILE_SIZE; break;
        case LEFT: head.x -= TILE_SIZE; break;
        case RIGHT: head.x += TILE_SIZE; break;
        default: break;
    }
}