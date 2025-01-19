#include "../include/score.hpp"

Score::Score(const std::string& text, const SDL_Rect& rect, TextMode mode, SDL_Color color, const std::string& fontPath, int fontSize)
    : score(0), mainText(text), textRedner(Text(mainText + std::to_string(score), rect, 0, mode, color, fontPath, fontSize)) {};
        

void Score::draw(SDL_Renderer* renderer){
    textRedner.draw(renderer); 
}

void Score::changeText(const std::string& new_text){
    mainText = new_text;
    textRedner.changeText(mainText + std::to_string(score));
}

void Score::changeScore(int new_score){
    score = new_score;
    textRedner.changeText(mainText + std::to_string(score));
}

void Score::incrementScore(int amount){
    score += amount;
    textRedner.changeText(mainText + std::to_string(score));
}





