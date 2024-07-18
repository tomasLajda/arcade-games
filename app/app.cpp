//
// Created by ja on 7/1/24.
//

#include "app.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <cassert>

#include "../scenes/arcadeScene.h"
#include "../scenes/gameScene.h"
#include "../games/BreakOut/breakOut.h"

App &App::Singleton() {
    static App theApp;
    return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag){
    mnoptrWindow = mScreen.Init(width, height, mag);

    std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();

    PushScene(std::move(arcadeScene));

    // Temporary
    {
        std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();

        std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));

        PushScene(std::move(breakoutScene));
    }

    return mnoptrWindow != nullptr;
}

void App::Run() {
    SDL_Event sdlEvent;
    bool running = true;

    uint32_t lastTick = SDL_GetTicks();
    uint32_t currentTick = lastTick;

    uint32_t deltaTime = 10;
    uint32_t accumulator = 0;

    mInputController.Init([&running](uint32_t deltaTime, InputState state){
        running = false;
    });

    while(running) {
        currentTick = SDL_GetTicks();
        uint32_t frameTime = currentTick - lastTick;

        if(frameTime > 300) {
            frameTime = 300;
        }

        lastTick = currentTick;

        accumulator += frameTime;

        // Input
        mInputController.Update(deltaTime);

        Scene *topScene = App::TopScene();
        assert(topScene && "Why dont we have a scene?");

        if(topScene) {
            // Update
            while(accumulator >= deltaTime) {
                // update current scene by deltaTime
                topScene->Update(deltaTime);
                accumulator -= deltaTime;
            }

            // Render
            topScene->Draw(mScreen);
        }

        mScreen.SwapScreens();
    }
}

void App::PushScene(std::unique_ptr<Scene> scene) {
    assert(scene && "Don't push nullprt!");

    if(scene) {
        scene->Init();
        mInputController.SetGameController(scene->GetGameController());
        mSceneStack.emplace_back(std::move(scene));
        SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetName().c_str());
    }
}

void App::PopScene() {
    if(mSceneStack.size() > 1) {
        mSceneStack.pop_back();
    }

    if(TopScene()) {
        mInputController.SetGameController(TopScene()->GetGameController());
        SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetName().c_str());
    }
}

Scene *App::TopScene() {
    if(mSceneStack.empty()) {
        return nullptr;
    }

    return mSceneStack.back().get();
}

const std::string &App::GetBasePath() {
    static std::string basePath = SDL_GetBasePath();

    return basePath;
}