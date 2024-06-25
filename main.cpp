#include <iostream>
#include "SDL2/SDL.h"

#include "graphics/color.h"
#include "shapes/line2D.h"
#include "shapes/triangle.h"
#include "shapes/AARectangle.h"
#include "shapes/circle.h"
#include "shapes/star2D.h"
#include "graphics/screen.h"

// based on pacman size
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int argc, const char * argv[]) {
    Screen screen;
    screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    Triangle triangle = Triangle(Vec2D(60, 10), Vec2D(10, 110), Vec2D(110, 110));
    AARectangle rectangle = AARectangle(Vec2D(100, 100), Vec2D(200, 200));
    Circle circle = Circle(Vec2D(100, 100), 50);
    Star2D star = Star2D(10, 20, Vec2D(100, 100), 6);
    screen.Draw(triangle, Color::Red());
    screen.Draw(rectangle, Color::White());
    screen.Draw(circle, Color::Yellow());
    screen.Draw(star, Color::Orange());
    screen.SwapScreens();

    SDL_Event sdlEvent;
    bool running = true;

    while(running) {
        while(SDL_PollEvent(&sdlEvent)) {
            switch(sdlEvent.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
    }

    return 0;
}



