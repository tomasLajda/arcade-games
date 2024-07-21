//
// Created by ja on 7/18/24.
//

#ifndef ARCADE_GAMES_TETRIS_H
#define ARCADE_GAMES_TETRIS_H

#include "../../shapes/AARectangle.h"
#include "../game.h"
#include "tetrimino.h"
#include "block.h"
#include <vector>

class Tetris: public Game {
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(u_int32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;
    virtual const std::string &GetName() const override;

    inline uint32_t GetGameSpeed() {return mGameSpeed;}
    inline void SetGameSpeed(uint32_t gameSpeed) {mGameSpeed = gameSpeed;}

private:
    void Reset();

private:
    AARectangle mBoundary;
    uint32_t mGameSpeed;
    uint32_t mLevel;
    Tetrimino mTetrimino;
    std::vector<BlockT> mBlocks;

};

#endif//ARCADE_GAMES_TETRIS_H
