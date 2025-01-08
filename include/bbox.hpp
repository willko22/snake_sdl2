#pragma  once
#include "globals.hpp"

struct Bbox {
    private:
        void updateDerivedProperties();
        void validatePosition();

    public:
        int x, y, x2, y2, w, h, center_x, center_y, area;
        SDL_Rect sdlRect;

        Bbox()
            :x(0), y(0), x2(0), y2(0),
            w(0), h(0), 
            center_x(0), center_y(0), 
            area(0),
            sdlRect({0,0,0,0}) {}

        inline Bbox(SDL_Rect rect) {
            setBbox(rect);
        }

        inline Bbox(int x1, int y1, int x2, int y2) {
            setBbox(x1, y1, x2, y2);
        }

        ~Bbox() = default;

        void setPos(int x, int y);
        void setBbox(const SDL_Rect& rect);
        void setBbox(int x1, int y1, int x2, int y2);
        void setDimensions(int w, int h);

        inline bool contains(int x, int y) const;
        inline bool contains(SDL_Rect& rect) const;
        inline bool intersects(SDL_Rect& rect) const;
        inline bool intersects(Bbox& other) const;
        inline void print() const;
        
        inline SDL_Rect* getRect() { return &sdlRect; }

        inline Bbox& operator=(const Bbox& other);
        inline Bbox& operator=(const SDL_Rect& rect);
        inline Bbox& operator=(const tuple<int, int, int, int>& coords);
        
};

void Bbox::setPos(int x, int y) {
    this->x = x;
    this->y = y;
    x2 = x + w;
    y2 = y + h;
    sdlRect = {x, y, w, h};
    updateDerivedProperties();
}

void Bbox::setBbox(const SDL_Rect& rect) {
    this->sdlRect = rect;
    x = rect.x;
    y = rect.y;
    x2 = rect.x + rect.w;
    y2 = rect.y + rect.h;
    w = rect.w;
    h = rect.h;
    updateDerivedProperties();
}

void Bbox::setBbox(int x1, int y1, int x2, int y2) {
    x = x1;
    y = y1;
    this->x2 = x2;
    this->y2 = y2;
    validatePosition();
    w = std::abs(x2 - x1);
    h = std::abs(y2 - y1);
    sdlRect = {x1, y1, w, h};
    updateDerivedProperties();
}

void Bbox::setDimensions(int new_w, int new_h) {
    w = new_w;
    h = new_h;
    x2 = x + w;
    y2 = y + h;
    sdlRect = {x, y, w, h};
    updateDerivedProperties();
}

inline void Bbox::updateDerivedProperties() {
    center_x = x + w / 2;
    center_y = y + h / 2;
    area = w * h;
}

inline void Bbox::validatePosition() {
    if (x > x2) {
        std::swap(x, x2);
    }
    if (y > y2) {
        std::swap(y, y2);
    }
}



inline bool Bbox::contains(int input_x, int input_y) const {
    return (x >= input_x && input_x <= x2 && y >= input_y && input_y <= y2);
}

inline bool Bbox::contains(SDL_Rect& rect) const {
    return SDL_HasIntersection(&sdlRect, &rect);
}

inline bool Bbox::intersects(SDL_Rect& rect) const {
    return SDL_HasIntersection(&sdlRect, &rect);
}

inline bool Bbox::intersects(Bbox& other) const {
    return SDL_HasIntersection(&sdlRect, &other.sdlRect);
}

inline void Bbox::print() const {
    std::cout << "x: " << x << " y: " << y << " x2: " << x2 << " y2: " << y2 << " w: " << w << " h: " << h << " center_x: " << center_x << " center_y: " << center_y << " area: " << area << std::endl;
}

// Overload assignment operator for SDL_Rect
inline Bbox& Bbox::operator=(const SDL_Rect& rect) {
    setBbox(rect);
    return *this;
}

// Overload assignment operator for coordinates
inline Bbox& Bbox::operator=(const std::tuple<int, int, int, int>& coords) {
    setBbox(std::get<0>(coords), std::get<1>(coords), std::get<2>(coords), std::get<3>(coords));
    return *this;
}

// Overload copy assignment operator
inline Bbox& Bbox::operator=(const Bbox& other) {
    if (this != &other) {
        this->sdlRect = other.sdlRect;
        this->x = other.x;
        this->y = other.y;
        this->x2 = other.x2;
        this->y2 = other.y2;
        this->w = other.w;
        this->h = other.h;
        this->center_x = other.center_x;
        this->center_y = other.center_y;
        this->area = other.area;
    }
    return *this;
}