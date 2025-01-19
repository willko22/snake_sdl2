#pragma once
#include "globals.hpp"
#include <typeinfo>


// using namespace std;

class Renderable {
    public:
        virtual void draw() {
            std::cout << typeid(*this).name() << " has no Draw method!" << std::endl;
        }
        virtual void draw(SDL_Renderer* renderer) {
            std::cout << typeid(*this).name() << " has no Draw method with SDL_Renderer!" << std::endl;
        }
};