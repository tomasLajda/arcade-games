//
// Created by ja on 7/2/24.
//

#ifndef ARCADE_GAMES_BREAKOUT_H
#define ARCADE_GAMES_BREAKOUT_H

#include "../game.h"
#include "paddle.h"
#include "ball.h"
#include "levelBoundary.h"
#include "breakOutLevel.h"

enum BreakOutGameStates {
    IN_PLAY = 0,
    IN_SERVE,
    IN_GAME_OVER
};

class BreakOut: public Game {
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(u_int32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;
    virtual const std::string &GetName() const override;

private:
    void ResetGame(size_t toLevel = 0);
    inline BreakOutLevel &GetCurrentLevel() {return mLevels[mCurrentLevel];}
    void SetToServeState();
    bool IsBallPassedCutoffY() const;
    void ReduceLifeByOne();
    inline bool IsGameOver() const {return mLives < 0;}

private:
    const int NUM_LIVES = 3;
    const float INITIAL_BALL_SPEED = 100;
    const Vec2D INITIAL_BALL_VELOCITY = Vec2D(100, -100);

    Paddle mPaddle;
    Ball mBall;
    LevelBoundary mLevelBoundary;
    std::vector<BreakOutLevel> mLevels;
    size_t mCurrentLevel;
    BreakOutGameStates mGameState;
    int mLives;
    float mCutoffY;
};


#endif//ARCADE_GAMES_BREAKOUT_H
