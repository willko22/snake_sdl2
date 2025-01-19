#pragma once
#include "renderable.hpp"
#include "globals.hpp"


// using namespace std;


class RenderManager {
    private:
        std::map<int, std::vector<Renderable*>> drawOrder;  // Using raw pointers
        SDL_Renderer* rendererPtr;
    public:
        inline RenderManager() : rendererPtr(nullptr) {}
        inline RenderManager(SDL_Renderer* renderer) : rendererPtr(renderer) {}
        ~RenderManager();

        inline void addElement(int index, Renderable* element);

        void reset();
        void drawAll();
        void drawLayer(int index);
        inline void addRenderer(SDL_Renderer* renderer) { rendererPtr = renderer; }

};

inline void RenderManager::addElement(int index, Renderable* element)
{
    // if the key does not exist, create a new vector
    if (drawOrder.find(index) == drawOrder.end())
    {
        drawOrder[index] = std::vector<Renderable*>();
    }

    // add the element to the vector
    drawOrder[index].push_back(element);
}

