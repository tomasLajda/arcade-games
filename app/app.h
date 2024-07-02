//
// Created by ja on 7/1/24.
//

#ifndef ARCADE_GAMES_APP_H
#define ARCADE_GAMES_APP_H

#include <cstdint>
#include <vector>
#include <memory>

#include "../scenes/scene.h"
#include "../graphics/screen.h"
#include "../input/inputController.h"


struct SDL_Window;

class App {
public:
    static App &Singleton();
    bool Init(uint32_t width, uint32_t height, uint32_t mag);
    void Run();

    inline uint32_t Width() const {return mScreen.Width();}
    inline uint32_t Height() const {return mScreen.Height();}

    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene *TopScene();

private:
    Screen mScreen;
    SDL_Window *mnoptrWindow;
    std::vector<std::unique_ptr<Scene>> mSceneStack;
    InputController mInputController;
};


#endif//ARCADE_GAMES_APP_H
