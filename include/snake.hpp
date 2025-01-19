#pragma once    // Include guard
#include "globals.hpp"
#include "renderable.hpp"

class Snake : public Renderable {
    private:
        SDL_Rect head;
        // vector<SDL_Rect> deleteSegments;
        std::list<SDL_Rect> body;
        int growAmount;
        Direction dir;
        unsigned int indexOfLastSegment = 0;
        unsigned int bodySize = 0;

        inline void moveHead();

    public:
        Snake(SDL_Rect initialHead) : head(initialHead), growAmount(INITIAL_SNAKE_SIZE), dir(STOP) {}
        ~Snake();
        void move();
        void draw(SDL_Renderer* renderer);

        inline void grow(int amount) { growAmount += amount; }
        inline bool checkCollision(SDL_Rect* other) const;
        inline bool checkCollisionSelf();
        inline void setDirection(Direction newDir) { dir = newDir; }
        inline const SDL_Rect& getHead() const { return head; }
        inline const Direction& getDirection() const { return dir; }
        inline std::list<SDL_Rect>* getBody() { return &body; }

        void reset(SDL_Rect initialHead);
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