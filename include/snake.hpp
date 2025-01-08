#pragma once    // Include guard
#include "globals.hpp"
#include "renderable.hpp"

class Snake : public Renderable {
    private:
        SDL_Rect head;
        SDL_Rect* headPtr;
        // vector<SDL_Rect> deleteSegments;
        deque<SDL_Rect> body;
        int growAmount = 0;
        Direction dir;

        inline void moveHead();

    public:
        Snake(SDL_Rect head);
        ~Snake();
        void move();
        void draw(SDL_Renderer* renderer);

        inline void grow(int amount) { growAmount += amount; }
        inline bool checkCollision(SDL_Rect* other) const;
        inline bool checkCollisionSelf();
        inline void setDirection(Direction newDir) { dir = newDir; }
        inline SDL_Rect getHead() const { return head; }
        inline Direction* getDirection() { return &dir; }
};

inline bool Snake::checkCollision(SDL_Rect* other) const{
    return SDL_HasIntersection(headPtr, other);
}

inline bool Snake::checkCollisionSelf(){
    for (SDL_Rect& segment : body) {
        if (SDL_HasIntersection(headPtr, &segment)) {
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