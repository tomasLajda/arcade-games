//
// Created by ja on 7/2/24.
//

#ifndef ARCADE_GAMES_BREAKOUT_H
#define ARCADE_GAMES_BREAKOUT_H

#include "../game.h"
#include "paddle.h"
#include "ball.h"
#include "levelBoundary.h"

class BreakOut: public Game {
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(u_int32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;
    virtual const std::string &GetName() const override;

private:
    void ResetGame();

    const Vec2D INITIAL_BALL_VELOCITY = Vec2D(100, -100);

    Paddle mPaddle;
    Ball mBall;
    LevelBoundary mLevelBoundary;
};


#endif//ARCADE_GAMES_BREAKOUT_H
