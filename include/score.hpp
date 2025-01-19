#pragma once
#include "globals.hpp"
#include "text.hpp"
#include "renderable.hpp"

class Score : public Renderable {
    private:
        int score;
        std::string mainText;
        Text textRedner;
    public:
        Score(const std::string& text, const SDL_Rect& rect, TextMode mode, SDL_Color color, const std::string& fontPath, int fontSize);
        
        inline ~Score() {}

        void draw(SDL_Renderer* renderer);
        void changeText(const std::string&  new_text);
        inline void changeColor(SDL_Color new_color) { changeColor(new_color); }
        inline void changeMode(TextMode new_mode) { changeMode(new_mode); }
        inline void changePosition(int new_x, int new_y) {changePosition(new_x, new_y); }
        inline void changeSize(int new_width, int new_height) { changeSize(new_width, new_height); }
        inline void changeRatio(int new_ratio) { changeRatio(new_ratio); }
        inline void changeFontPath(const std::string& new_font) { changeFontPath(new_font); }

        void changeScore(int new_score);
        void incrementScore(int amount = 1);
        inline int getScore() const { return score; }
};