//
// Created by ja on 6/10/24.
//

#ifndef ARCADE_GAMES_SCREEN_H
#define ARCADE_GAMES_SCREEN_H

#include <cstdint>
#include <vector>

#include "screenBuffer.h"
#include "color.h"

class Vec2D;
class Line2D;
class Star2D;
class Triangle;
class AARectangle;
class Circle;
class Shape;

struct SDL_Window;
struct SDL_Surface;

class Screen {
public:
    Screen();
    ~Screen();

    SDL_Window *Init(uint32_t w, uint32_t h, uint32_t mag);
    void SwapScreens();

    inline void SetClearColor(const Color &clearColor) {mClearColor = clearColor;}
    inline uint32_t Width() const { return mWidth;}
    inline uint32_t Height() const { return mHeight;}

    // Draw Methods

    void Draw(int x, int y, const Color& color);
    void Draw(const Vec2D &point, const Color &color);
    void Draw(const Line2D &line, const Color &color);
    void Draw(const Star2D &star, const Color &color);
    void Draw(const Triangle &triangle, const Color &color, bool fill = false, const Color &fillColor = Color::White());
    void Draw(const AARectangle &rectangle, const Color &color, bool fill = false, const Color &fillColor = Color::White());
    void Draw(const Circle &circle, const Color &color, bool fill = false, const Color &fillColor = Color::White());
private:
    // Blocks copying a class
    Screen(const Screen &screen);
    Screen &operator=(const Screen &screen);

    void ClearScreen();
    void FillPoly(const std::vector<Vec2D> &points, const Color &color);
    void FillPoly(const Shape &shape, const Color &color);

    uint32_t mWidth;
    uint32_t mHeight;

    ScreenBuffer mBackBuffer;

    SDL_Window *moptrWindow;
    SDL_Surface *mnoptrWindowSurface;

    Color mClearColor;
};


#endif//ARCADE_GAMES_SCREEN_H
