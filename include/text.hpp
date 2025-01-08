#pragma once
#include "globals.hpp"
#include "renderable.hpp"


class Text : public Renderable{
    private:
        TTF_Font* font;
        string fontPath, text;
        int fontSize, fontSizeBck;
        SDL_Color color;
        TextMode mode;
        SDL_Rect rect;
        float ratio;

        
        void drawNormal(SDL_Renderer* renderer);
        void drawFit(SDL_Renderer* renderer);
        void drawCentered(SDL_Renderer* renderer);
        void drawRatio(SDL_Renderer* renderer);
        void calculateFontSize(const string& text);

    public:
        Text(const string& text, const SDL_Rect& rect, float ratio, TextMode mode, SDL_Color color, const string& fontPath, int fontSize);
        ~Text();
        
        using Renderable::draw;
        void draw(SDL_Renderer* renderer);

        inline void changeColor(SDL_Color new_color) { color = new_color; }
        inline void changeMode(TextMode new_mode) { mode = new_mode; }
        inline void changePosition(int new_x, int new_y) { rect.x = new_x; rect.y = new_y; }
        inline void changeSize(int new_width, int new_height) { rect.w = new_width; rect.h = new_height; }
        inline void changeRatio(int new_ratio) { ratio = new_ratio; }
        inline void changeFontPath(const string& new_fontPath) { fontPath = new_fontPath; }
        inline void changeText(const string& new_text) { text = new_text; }

        inline SDL_Rect getRect() const { return rect; }
        inline string getText() const { return text; }
        inline SDL_Color getColor() const { return color; }
        inline TextMode getMode() const { return mode; }
        inline TTF_Font* getFont() const { return font; }
        inline int getRatio() const { return ratio; }
};

inline void cleanTextRender(SDL_Surface* surface, SDL_Texture* texture){
    if (surface) {
        SDL_FreeSurface(surface);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}