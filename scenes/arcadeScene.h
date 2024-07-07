//
// Created by ja on 7/1/24.
//

#ifndef ARCADE_GAMES_ARCADESCENE_H
#define ARCADE_GAMES_ARCADESCENE_H

#include "scene.h"
#include <memory>

enum eGame {
    TETRIS = 0,
    BREAK_OUT,
    ASTEROIDS,
    PACMAN,
    NUM_GAMES
};

class ArcadeScene: public Scene {
public:
    ArcadeScene();
    virtual void Init() override;
    virtual void Update(u_int32_t deltaTime) override;
    virtual void Draw(Screen &theScreen) override;
    virtual const std::string &GetName() const override;

private:
    std::unique_ptr<Scene> GetScene(eGame game);
};


#endif//ARCADE_GAMES_ARCADESCENE_H
