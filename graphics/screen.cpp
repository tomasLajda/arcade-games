//
// Created by ja on 6/10/24.
//

#include "screen.h"
#include "../shapes/line2D.h"
#include "../shapes/star2D.h"
#include "../shapes/triangle.h"
#include "../shapes/shape.h"
#include "../shapes/circle.h"
#include "../shapes/AARectangle.h"
#include "../utils/utils.h"

#include <SDL2/SDL.h>
#include <cassert>
#include <cmath>
#include <algorithm>

Screen::Screen(): mWidth(0), mHeight(0), moptrWindow(nullptr), mnoptrWindowSurface(nullptr) {}
Screen::~Screen() {
    if(moptrWindow){
        SDL_DestroyWindow(moptrWindow);
        moptrWindow = nullptr;
    }
    SDL_Quit();
}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag){
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "Error SDL_Init failed" << std::endl;
        return nullptr;
    }

    mWidth = w;
    mHeight = h;

    moptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

    assert(moptrWindow);

    if(moptrWindow){
        mnoptrWindowSurface = SDL_GetWindowSurface(moptrWindow);

        SDL_PixelFormat *pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

        Color::InitColorFormat(pixelFormat);
        mClearColor = Color::Black();

        mBackBuffer.Init(pixelFormat->format, mWidth, mHeight);
        mBackBuffer.Clear(mClearColor);
    }

    return moptrWindow;
}

void Screen::SwapScreens() {
    assert(moptrWindow);

    if(moptrWindow) {
        ClearScreen();

        SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mnoptrWindowSurface, nullptr);

        SDL_UpdateWindowSurface(moptrWindow);

        mBackBuffer.Clear(mClearColor);
    }

}

void Screen::Draw(int x, int y, const Color& color) {
    assert(moptrWindow);

    if(moptrWindow) {
        mBackBuffer.SetPixel(color, x, y);

    }
}

void Screen::Draw(const Vec2D &point, const Color &color) {
    assert(moptrWindow);

    if(moptrWindow) {
        mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
    }
}

void Screen::Draw(const Line2D &line, const Color &color) {
    assert(moptrWindow);

    if(moptrWindow) {
        int dx, dy;

        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1 - x0;
        dy = y1 - y0;

        const signed char ix((dx > 0) - (dx < 0)); // evaluate to 1 or -1;
        const signed char iy((dy > 0) - (dy < 0));

        dx = abs(dx) * 2;
        dy = abs(dy) * 2;

        Draw(x0, y0, color);

        if(dx >= dy) {
            int d = dy - dx/2;

            while(x0 != x1) {
                if(d >= 0) {
                    d -= dx;
                    y0 += iy;
                }

                d += dy;
                x0 += ix;

                Draw(x0, y0, color);
            }
        }
        else {
            int d = dx - dy/2;

            while(y0 != y1) {
                if(d >= 0) {
                    d -= dy;
                    x0 += ix;
                }

                d += dx;
                y0 += iy;

                Draw(x0, y0, color);
            }
        }

    }
}

void Screen::Draw(const Star2D &star, const Color &color) {
    auto edges = star.GetEdges();

    for (int i = 0; i < star.GetSpikes() * 2; ++i) {
        Draw(edges[i], color);
    }
}

void Screen::Draw(const Triangle &triangle, const Color &color, bool fill, const Color &fillColor){
    if(fill) {
        FillPoly(triangle.GetPoints(), fillColor);
    }

    Line2D p0p1 = Line2D(triangle.GetP0(), triangle.GetP1());
    Line2D p1p2 = Line2D(triangle.GetP1(), triangle.GetP2());
    Line2D p2p0 = Line2D(triangle.GetP2(), triangle.GetP0());

    Draw(p0p1, color);
    Draw(p1p2, color);
    Draw(p2p0, color);
}

void Screen::Draw(const AARectangle &rectangle, const Color &color, bool fill, const Color &fillColor) {
    auto points = rectangle.GetPoints();

    if(fill) {
        FillPoly(points, fillColor);
    }

    Line2D p0p1 = Line2D(points[0], points[1]);
    Line2D p1p2 = Line2D(points[1], points[2]);
    Line2D p2p3 = Line2D(points[2], points[3]);
    Line2D p3p0 = Line2D(points[3], points[0]);

    Draw(p0p1, color);
    Draw(p1p2, color);
    Draw(p2p3, color);
    Draw(p3p0, color);
}

void Screen::Draw(const Circle &circle, const Color &color, bool fill, const Color &fillColor) {
//    if(fill) {
//        FillPoly(circle, fillColor);
//    }

    static unsigned NUM_CIRCLE_SEGMENTS = 30;

    std::vector<Vec2D> circlePoints;
    std::vector<Line2D> lines;

    float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);

    Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vec2D p1 = p0;
    Line2D nextLineToDraw;

    for(unsigned i = 0; i < NUM_CIRCLE_SEGMENTS; ++i) {
        p1.Rotate(angle, circle.GetCenterPoint());
        nextLineToDraw.SetP1(p1);
        nextLineToDraw.SetP0(p0);

        lines.push_back(nextLineToDraw);
//        Draw(nextLineToDraw, color);
        p0 = p1;
        circlePoints.push_back(p0);
    }

    if(fill) {
        FillPoly(circlePoints, fillColor);
    }

    for(const Line2D &line : lines) {
        Draw(line, color);
    }
}

void Screen::ClearScreen(){
    assert(moptrWindow);

    if(moptrWindow){
        SDL_FillRect(mnoptrWindowSurface, nullptr, mClearColor.GetPixelColor());
    }
}

void Screen::FillPoly(const std::vector<Vec2D> &points, const Color &color) {
    if(points.size() > 0) {
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float right = points[0].GetX();
        float left = points[0].GetX();

        for(size_t i = 1; i < points.size(); ++i) {
            if(points[i].GetY() < top) {
                top = points[i].GetY();
            }
            if(points[i].GetY() > bottom) {
                bottom = points[i].GetY();
            }
            if(points[i].GetX() < left) {
                left = points[i].GetX();
            }
            if(points[i].GetX() > right) {
                right = points[i].GetX();
            }
        }

        for(int y = top; y < bottom; y++) {
            std::vector<float> nodeXVec;
            size_t j = points.size() - 1;
            for (size_t i = 0; i < points.size(); ++i) {
                float pointiY = points[i].GetY();
                float pointjY = points[j].GetY();

                if((pointiY <= (float) y && pointjY > (float)y) || (pointjY <= (float)y && pointiY > (float)y)) {
                    float denom = pointjY - pointiY;
                    if(IsEqual(denom, 0)) {
                        continue;
                    }

                    float x = points[i].GetX() + (y - pointiY)/(denom) * (points[j].GetX() - points[i].GetX());
                    nodeXVec.push_back(x);
                }
                j = i;
            }
            std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

            for(size_t k = 0; k < nodeXVec.size(); k+=2) {
                if(nodeXVec[k] > right) {
                    break;
                }

                if(nodeXVec[k+1] > left) {
                    if(nodeXVec[k] < left) {
                        nodeXVec[k] = left;
                    }

                    if(nodeXVec[k+1] > right) {
                        nodeXVec[k+1] = right;
                    }

                    for (int x = nodeXVec[k]; x < nodeXVec[k+1]; ++x) {
                        Draw(x, y, color);
                    }
                }
            }
        }
    }
}

void Screen::FillPoly(const Shape &shape, const Color &color) {
    auto points = shape.GetPoints();

    if(points.size() > 0) {
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float right = points[0].GetX();
        float left = points[0].GetX();


        for(size_t i = 1; i < points.size(); ++i) {
            if(points[i].GetY() < top) {
                top = points[i].GetY();
            }
            if(points[i].GetY() > bottom) {
                bottom = points[i].GetY();
            }
            if(points[i].GetX() < left) {
                left = points[i].GetX();
            }
            if(points[i].GetX() > right) {
                right = points[i].GetX();
            }
        }

        const Circle* circle = dynamic_cast<const Circle*>(&shape);
        if(circle != nullptr) {
            top = points[0].GetY() - circle->GetRadius();
            bottom = points[0].GetY() + circle->GetRadius();
            right = points[0].GetX() + circle->GetRadius();
            left = points[0].GetX() - circle->GetRadius();
        }

        for(int y = top; y <= bottom; y++) {
            for (int x = left; x <= right; ++x) {
                if(shape.ContainsPoint(Vec2D(x, y))) {
                    Draw(x, y, color);
                }
            }
        }
    }
}
