#pragma once
#include "globals.hpp"
#include <typeinfo>


using namespace std;

class Renderable {
    public:
        virtual void draw() {
            cout << typeid(*this).name() << " has no Draw method!" << endl;
        }
        virtual void draw(SDL_Renderer* renderer) {
            cout << typeid(*this).name() << " has no Draw method with SDL_Renderer!" << endl;
        }
};