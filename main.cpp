#include <iostream>
#include <SDL2/SDL.h>

#include "./app/app.h"

// based on pacman size
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int argc, const char * argv[]) {
    if(App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION)) {
        App::Singleton().Run();
    }

    return 0;
}



