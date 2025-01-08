#include "../include/text.hpp"


Text::Text(const string& text, const SDL_Rect& rect, float ratio, TextMode mode, SDL_Color color, const string& fontPath, int fontSize)
    : fontPath(fontPath), text(text), fontSize(fontSize), fontSizeBck(fontSize), color(color), mode(mode), rect(rect), ratio(ratio){
    
    this->font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        // Handle error
        throw runtime_error("Failed to load font: " + fontPath);
    }
}

Text::~Text(){
    if (font) {
        TTF_CloseFont(font);
    }
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
    SDL_Surface*  surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) throw runtime_error("Failed to render text: " + string(TTF_GetError()));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) throw runtime_error("Failed to create texture: " + string(SDL_GetError()));
    SDL_Rect dest = {rect.x, rect.y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &dest);
    cleanTextRender(surface, texture);

}

void Text::drawFit(SDL_Renderer* renderer){
    calculateFontSize(text);
    SDL_Surface*  surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) throw runtime_error("Failed to render text: " + string(TTF_GetError()));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) throw runtime_error("Failed to create texture: " + string(SDL_GetError()));
    SDL_Rect dest = {rect.x, rect.y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &dest);
    cleanTextRender(surface, texture);

}

void Text::drawCentered(SDL_Renderer* renderer){
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) throw runtime_error("Failed to render text: " + string(TTF_GetError()));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) throw runtime_error("Failed to create texture: " + string(SDL_GetError()));
    SDL_Rect dest = {
        rect.x - surface->w/2, 
        rect.y - surface->h/2, 
        surface->w, 
        surface->h
    };

    if (SDL_RenderCopy(renderer, texture, NULL, &dest) != 0) {
        throw runtime_error("Failed to render copy: " + string(SDL_GetError()));
    }

    cleanTextRender(surface, texture);

}

void Text::drawRatio(SDL_Renderer* renderer){
    SDL_Surface*  surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) throw runtime_error("Failed to render text: " + string(TTF_GetError()));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) throw runtime_error("Failed to create texture: " + string(SDL_GetError()));
    SDL_Rect dest = {
        static_cast<int>(rect.x - round(surface->w * ratio)),
        static_cast<int>(rect.y - round(surface->h * ratio)), 
        surface->w, 
        surface->h
    };

    SDL_RenderCopy(renderer, texture, NULL, &dest);
    cleanTextRender(surface, texture);
}


void Text::calculateFontSize(const string& text){
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



