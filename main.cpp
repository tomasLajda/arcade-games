#include <iostream>
#include "SDL2/SDL.h"

#include "graphics/color.h"
#include "shapes/line2D.h"
#include "shapes/star2D.h"
#include "graphics/screen.h"

// based on pacman size
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int argc, const char * argv[]) {
    Screen screen;
    screen.Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);

    Star2D line = Star2D(10, 50, 100, 100, 6);
    screen.Draw(line, Color::White());
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



