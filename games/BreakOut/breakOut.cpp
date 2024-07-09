//
// Created by ja on 7/2/24.
//

#include "breakOut.h"
#include "../../input/gameController.h"
#include "../../app/app.h"
#include "../../shapes/circle.h"

void BreakOut::Init(GameController &controller) {
    controller.ClearAll();

    ResetGame();

    ButtonAction serveAction;
    serveAction.key = GameController::ActionKey();
    serveAction.action = [this](uint32_t deltaTime, InputState state) {
        if(mGameState == IN_SERVE) {
            if(GameController::IsPressed(state)) {
                mGameState = IN_PLAY;

                if(mPaddle.IsMovingLeft()) {
                    mBall.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
                else {
                    mBall.SetVelocity(Vec2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
            }
        }
        else if(mGameState == IN_GAME_OVER) {
            if(GameController::IsPressed(state)) {
                ResetGame();
            }
        }
    };

    controller.AddInputActionForKey(serveAction);

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(mGameState == IN_PLAY || mGameState == IN_SERVE) {
            if(GameController::IsPressed(state)) {
                mPaddle.SetMovementDirection(PaddleDirection::LEFT);
            }
            else {
                mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
            }
        }
    };

    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(mGameState == IN_PLAY || mGameState == IN_SERVE) {
            if (GameController::IsPressed(state)) {
                mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
            } else {
                mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
            }
        }
    };

    controller.AddInputActionForKey(rightKeyAction);
}

void BreakOut::Update(u_int32_t deltaTime) {
    if(mGameState == IN_SERVE) {
        mPaddle.Update(deltaTime, mBall);
        SetToServeState();
    }
    else if (mGameState == IN_PLAY) {
        mBall.Update(deltaTime);
        mPaddle.Update(deltaTime, mBall);

        BoundaryEdge edge;


        if(mPaddle.Bounce(mBall)) {
            return;
        }

        if(mLevelBoundary.HasCollided(mBall, edge)) {
            mBall.Bounce(edge);
        }

        GetCurrentLevel().Update(deltaTime, mBall);
    }

    if(IsBallPassedCutoffY()) {
        ReduceLifeByOne();
        if(!IsGameOver()) {
            SetToServeState();
        }
        else {
            mGameState = IN_GAME_OVER;
        }
    }
    else if(GetCurrentLevel().IsLevelComplete()) {
        mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
        ResetGame(mCurrentLevel);
    }

}

void BreakOut::Draw(Screen &screen) {
    mBall.Draw(screen);
    mPaddle.Draw(screen);
    GetCurrentLevel().Draw(screen);
    screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());

    Circle lifeCircle(Vec2D(10, App::Singleton().Height() - 10), 5);

    Line2D cutoff(Vec2D(0, mCutoffY), Vec2D(App::Singleton().Width(), mCutoffY));
    screen.Draw(cutoff, Color::White());

    for(int i = 0; i < mLives; ++i) {
        screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
        lifeCircle.MoveBy(Vec2D(17, 0));
    }
}

const std::string &BreakOut::GetName() const {
    static std::string name = "Break Out!";
    return name;
}

void BreakOut::ResetGame(size_t toLevel) {
    mCutoffY = App::Singleton().Height() - 2*Paddle::PADDLE_HEIGHT;
    mLives = NUM_LIVES;
    mCurrentLevel = toLevel;

    mLevels = BreakOutLevel::LoadLevelsFromFile(App::GetBasePath() + "assets/BreakoutLevels.txt");

    AARectangle paddleRect = AARectangle(Vec2D(App::Singleton().Width()/2 - Paddle::PADDLE_WIDTH/2, App::Singleton().Height() - 3*Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT);
    AARectangle levelBoundary = AARectangle(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height());

    mLevelBoundary = LevelBoundary(levelBoundary);

    mPaddle.Init(paddleRect, levelBoundary);

    mBall.MoveTo(Vec2D(App::Singleton().Width()/2.0f, App::Singleton().Height() * 0.75f));
    mBall.SetVelocity(INITIAL_BALL_VELOCITY);

    SetToServeState();
}

void BreakOut::SetToServeState() {
    mGameState = IN_SERVE;
    mBall.Stop();

    mBall.MoveTo(Vec2D(mPaddle.GetAARectangle().GetCenterPoint().GetX(), mPaddle.GetAARectangle().GetTopLeftPoint().GetY() - mBall.GetRadius() - 1));
}

bool BreakOut::IsBallPassedCutoffY() const {
    return mBall.GetPosition().GetY() > mCutoffY;
}

void BreakOut::ReduceLifeByOne() {
    if(mLives >= 0) {
        --mLives;
    }
}