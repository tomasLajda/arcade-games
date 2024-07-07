//
// Created by ja on 7/1/24.
//

#ifndef ARCADE_GAMES_GAMESCENE_H
#define ARCADE_GAMES_GAMESCENE_H

#include "scene.h"
#include "../games/game.h"
#include <memory>

class GameScene: public Scene {
public:
    GameScene(std::unique_ptr<Game> optrGame);
    virtual ~GameScene() {}
    virtual void Init() override;
    virtual void Update(uint32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;

    virtual const std::string &GetName() const override;

private:
    std::unique_ptr<Game> mGame;
};


#endif//ARCADE_GAMES_GAMESCENE_H
