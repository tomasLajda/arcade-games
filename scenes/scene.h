//
// Created by ja on 7/1/24.
//

#ifndef ARCADE_GAMES_SCENE_H
#define ARCADE_GAMES_SCENE_H

#include <string>

#include "../input/gameController.h"

class Screen;

// Interface
class Scene {
public:
    virtual ~Scene() {}
    virtual void Init() = 0;
    virtual void Update(u_int32_t deltaTime) = 0;
    virtual void Draw(Screen &theScreen) = 0;
    virtual const std::string &GetSceneName() const = 0;

    GameController *GetGameController() {return &mGameController;}

protected:
    GameController mGameController;
};

#endif//ARCADE_GAMES_SCENE_H
