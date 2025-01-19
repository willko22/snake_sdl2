#pragma once
#include "globals.hpp"
#include "text.hpp"
#include "renderable.hpp"

// this will be rendering debuf info on the screen
struct _debugInfo {
    int target_fps;
    int current_fps;
    int calc_per_sec;
};

class DebugInfo : public Renderable {
    private:
        _debugInfo info = {TARGET_FPS, 0, 0};
        std::string text;
        Text textRender;
    public:
        DebugInfo();
        
        inline ~DebugInfo() {}

        void draw(SDL_Renderer* renderer);
        inline void updateFPS(const int &fps) { info.current_fps = fps; }
        inline void updateCalcFPS(const int &fps) { info.calc_per_sec = fps; }
        inline void updateTargetFPS(const int &fps) { info.target_fps = fps; }
};