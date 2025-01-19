#include "../include/debugInfo.hpp"

DebugInfo::DebugInfo()
    : text("MAX FPS: " + std::to_string(info.target_fps) + " | Calc/s: " + std::to_string(info.calc_per_sec)),
      textRender(Text(text, {0, 0, 0, 0}, 0, NORMAL, DEBUG_TEXT_COLOR, DEBUG_FONT_PATH, DEBUG_FONT_SIZE)) {}
 

void DebugInfo::draw(SDL_Renderer* renderer) {
    if (DEBUG_MOD == false) return;
    text = "MAX FPS: " + std::to_string(info.target_fps) + " | Calc/s: " + std::to_string(info.calc_per_sec) ;
    textRender.changeText(text);
    textRender.draw(renderer);
}  