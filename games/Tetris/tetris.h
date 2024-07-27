//
// Created by ja on 7/18/24.
//

#ifndef ARCADE_GAMES_TETRIS_H
#define ARCADE_GAMES_TETRIS_H

#include "../../shapes/AARectangle.h"
#include "../game.h"
#include "blockT.h"
#include "tetrimino.h"
#include "tetrisLevel.h"
#include <vector>
#include <SDL2/SDL_ttf.h>

class Tetris: public Game {
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(u_int32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;
    virtual const std::string &GetName() const override;


private:
    void Reset();

private:
    AARectangle mBoundary;
    Tetrimino mTetrimino;
    TetrisLevel mLevel;
};

#endif//ARCADE_GAMES_TETRIS_H
