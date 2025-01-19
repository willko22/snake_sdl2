#pragma once
#include "globals.hpp"
#include "renderable.hpp"

class Food : public Renderable {
    private:
        SDL_Rect rect;
        SDL_Color color;
        SDL_Rect randomBounds;
        int modifier;

    public:

        inline Food(const SDL_Rect& rect, const SDL_Color& sdlColor, int modif, const SDL_Rect& bounds)
            : rect(rect), color(sdlColor), randomBounds(bounds), modifier(modif){};
        ~Food();
        
        void draw(SDL_Renderer* renderer);
       
        inline void setPos(int x, int y) { rect.x = x; rect.y = y; }
        inline void setColor(const SDL_Color& newColor) { color = newColor; }
        inline void setModifier(int newModifier) { modifier = newModifier; }
        void setRandomPosition(const std::vector<SDL_Rect>& snakeBody);

        inline const SDL_Rect& getRect() const { return rect; }

        inline int getModifier() const { return modifier; }

};
