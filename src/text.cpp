#include "../include/text.hpp"


Text::Text(const std::string& text, const SDL_Rect& rect, float ratio, TextMode mode, SDL_Color color, const std::string& fontPath, int fontSize)
    : fontPath(fontPath), text(text), fontSize(fontSize), fontSizeBck(fontSize), color(color), mode(mode), rect(rect), ratio(ratio)
    {

    this->font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        // Handle error
        throw std::runtime_error("Failed to load font: " + fontPath);
    }
 
    if (mode == FIT) calculateFontSize(text);
    if (!surface) create_surface();
}

Text::~Text(){
    if (font) {
        TTF_CloseFont(font);
    }
    if (surface) { 
        SDL_FreeSurface(surface);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }
} 


void Text::create_surface(){
 
    if (surface) SDL_FreeSurface(surface); 
    surface = TTF_RenderText_Solid(font, text.c_str(), color); 
    if (!surface) throw std::runtime_error("Failed to create surface with text: " + std::string(TTF_GetError()));

    recalcTexture = true;

}

void Text::create_texture(SDL_Renderer* renderer){

    if (texture) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
    recalcTexture = false;

}


void Text::draw(SDL_Renderer* renderer){
    switch(mode){
        case NORMAL: drawNormal(renderer); break;
        case FIT: drawFit(renderer); break;
        case CENTERED: drawCentered(renderer); break;
        case RATIO: drawRatio(renderer); break;
        default: break;
    }
}

void Text::drawNormal(SDL_Renderer* renderer){
    SDL_Rect dest = {rect.x, rect.y, surface->w, surface->h};

    if (recalcTexture) { create_texture(renderer); }
    if (SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
        throw std::runtime_error("Failed to render copy: " + std::string(SDL_GetError()));
    }

}

void Text::drawFit(SDL_Renderer* renderer){
    if (ratioChanged) {
        calculateFontSize(text);
        create_surface();
        ratioChanged = false;
    }

    SDL_Rect dest = {rect.x, rect.y, surface->w, surface->h};

    if (recalcTexture) { create_texture(renderer); }
    if (SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
        throw std::runtime_error("Failed to render copy: " + std::string(SDL_GetError()));
    }
}

void Text::drawCentered(SDL_Renderer* renderer){
    SDL_Rect dest = {
        rect.x - surface->w/2, 
        rect.y - surface->h/2, 
        surface->w, 
        surface->h 
    };

    if (recalcTexture) { create_texture(renderer); }
    if (SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
        throw std::runtime_error("Failed to render copy: " + std::string(SDL_GetError()));
    }
}

void Text::drawRatio(SDL_Renderer* renderer){

    SDL_Rect dest = {
        static_cast<int>(rect.x - round(surface->w * ratio)),
        static_cast<int>(rect.y - round(surface->h * ratio)), 
        surface->w, 
        surface->h
    };

    if (recalcTexture) { create_texture(renderer); }
    if (SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
        throw std::runtime_error("Failed to render copy: " + std::string(SDL_GetError()));
    }

}


void Text::calculateFontSize(const std::string& text){
    int fontSize = TTF_FontHeight(font);
    int textWidth = 0;
    int textHeight = 0;
    const char* text_c = text.c_str();

    TTF_SizeText(font, text_c, &textWidth, &textHeight);

    while (textWidth > rect.w || textHeight > rect.h){
        fontSize -= 2;
        font = TTF_OpenFont("path/to/font.ttf", fontSize);
        TTF_SizeText(font, text_c, &textWidth, &textHeight);
    }
}   


void Text::changeColor(SDL_Color new_color){
    color = new_color;
    create_surface();

}

void Text::changeFontPath(const std::string& new_fontPath){
    fontPath = new_fontPath;

    if (font) TTF_CloseFont(font);  
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    
    create_surface();
}

void Text::changeText(const std::string& new_text){
    text = new_text;
    // cPrint(text); 
    if (mode == TextMode::FIT) {
        calculateFontSize(text);
    }

    create_surface();
}