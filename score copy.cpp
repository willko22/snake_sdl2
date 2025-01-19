#include "../include/score.hpp"


void Score::draw(SDL_Renderer* renderer){
    Text::draw(renderer); 
}

void Score::changeText(const std::string& new_text){
    mainText = new_text;
    Text::changeText(mainText + std::to_string(score));
}

void Score::changeScore(int new_score){
    score = new_score;
    Text::changeText(mainText + std::to_string(score));
}

void Score::incrementScore(int amount){
    score += amount;
    Text::changeText(mainText + std::to_string(score));
}





