//
// Created by ja on 7/2/24.
//

#include "breakOut.h"
#include "../../input/gameController.h"
#include "../../app/app.h"

void BreakOut::Init(GameController &controller) {
    controller.ClearAll();
    ResetGame();

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mPaddle.SetMovementDirection(PaddleDirection::LEFT);
        }
        else {
            mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
        }
    };

    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
        }
        else {
            mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
        }
    };

    controller.AddInputActionForKey(rightKeyAction);
}

void BreakOut::Update(u_int32_t deltaTime) {
    mBall.Update(deltaTime);
    mPaddle.Update(deltaTime, mBall);

    BoundaryEdge edge;


    if(mPaddle.Bounce(mBall)) {
        return;
    }

    if(mLevelBoundary.HasCollided(mBall, edge)) {
        mBall.Bounce(edge);
    }
}

void BreakOut::Draw(Screen &screen) {
    mBall.Draw(screen);
    mPaddle.Draw(screen);
    screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());
}

const std::string &BreakOut::GetName() const {
    static std::string name = "Break Out!";
    return name;
}

void BreakOut::ResetGame() {
    AARectangle paddleRect = AARectangle(Vec2D(App::Singleton().Width()/2 - Paddle::PADDLE_WIDTH/2, App::Singleton().Height() - 3*Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT);
    AARectangle levelBoundary = AARectangle(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height());

    mLevelBoundary = LevelBoundary(levelBoundary);

    mPaddle.Init(paddleRect, levelBoundary);

    mBall.MoveTo(Vec2D(App::Singleton().Width()/2.0f, App::Singleton().Height()/2.0f));
    mBall.SetVelocity(INITIAL_BALL_VELOCITY);
}