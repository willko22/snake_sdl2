#pragma once
#include "globals.hpp"
#include "text.hpp"

class Score : public Text {
    private:
        int score;
        string mainText;
    public:
        inline Score(const string& text, const SDL_Rect& rect, TextMode mode, SDL_Color color, const string& fontPath, int fontSize)
            : Text(text + to_string(0), rect, 0, mode, color, fontPath, fontSize), score(0) 
        {
            mainText = text;
        }
        
        inline ~Score() {}

        void draw(SDL_Renderer* renderer);
        void changeText(const string&  new_text);
        inline void changeColor(SDL_Color new_color) { Text::changeColor(new_color); }
        inline void changeMode(TextMode new_mode) { Text::changeMode(new_mode); }
        inline void changePosition(int new_x, int new_y) { Text::changePosition(new_x, new_y); }
        inline void changeSize(int new_width, int new_height) { Text::changeSize(new_width, new_height); }
        inline void changeRatio(int new_ratio) { Text::changeRatio(new_ratio); }
        inline void changeFontPath(const string& new_font) { Text::changeFontPath(new_font); }

        void changeScore(int new_score);
        void incrementScore(int amount = 1);
        inline int getScore() const { return score; }
};