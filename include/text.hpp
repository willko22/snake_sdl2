#pragma once
#include "globals.hpp"
#include "renderable.hpp"



class Text : public Renderable{
    private:
        TTF_Font* font;
        std::string fontPath, text;
        int fontSize, fontSizeBck;
        SDL_Color color;
        TextMode mode;
        SDL_Rect rect;
        float ratio;
        bool ratioChanged = true, recalcTexture = true;

        SDL_Surface* surface = nullptr;
        SDL_Texture* texture = nullptr;

        
        void drawNormal(SDL_Renderer* renderer);
        void drawFit(SDL_Renderer* renderer);
        void drawCentered(SDL_Renderer* renderer);
        void drawRatio(SDL_Renderer* renderer);
        void calculateFontSize(const std::string& text);
        void create_surface();
        void create_texture(SDL_Renderer* renderer);

    public:
        Text() {};
        Text(const std::string& text, const SDL_Rect& rect, float ratio, TextMode mode, SDL_Color color, const std::string& fontPath, int fontSize);
        ~Text();
        
        using Renderable::draw;
        void draw(SDL_Renderer* renderer);

        inline void changeMode(TextMode new_mode)               { mode = new_mode; }
        inline void changePosition(int new_x, int new_y)        { rect.x = new_x; rect.y = new_y; }
        inline void changeSize(int new_width, int new_height)   { rect.w = new_width; rect.h = new_height; }
        inline void changeRatio(int new_ratio)                  { ratio = new_ratio; }
        void changeColor(SDL_Color new_color);
        void changeFontPath(const std::string& new_fontPath);
        void changeText(const std::string& new_text);

        void changeFontSize(int new_size) { 
            fontSize = new_size; 
            fontSizeBck = new_size; 
            if (font) TTF_CloseFont(font);
            font = TTF_OpenFont(fontPath.c_str(), fontSize);  
            create_surface();
        }

        inline SDL_Rect getRect() const { return rect; }
        inline std::string getText() const { return text; }
        inline SDL_Color getColor() const { return color; }
        inline TextMode getMode() const { return mode; }
        inline TTF_Font* getFont() const { return font; }
        inline int getRatio() const { return ratio; }

};
