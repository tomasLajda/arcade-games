//
// Created by ja on 7/18/24.
//

#include "tetris.h"

void Tetris::Init(GameController &controller) {
    srand(time(0));

    controller.ClearAll();

    Reset();

    ButtonAction leftKeyAction;

    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(Tetrimino::LEFT);
        }
        else {
            mTetrimino.UnsetControl(Tetrimino::LEFT);
        }
    };

    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(Tetrimino::RIGHT);
        }
        else {
            mTetrimino.UnsetControl(Tetrimino::RIGHT);
        }
    };

    controller.AddInputActionForKey(rightKeyAction);

    ButtonAction upKeyAction;
    upKeyAction.key = GameController::UpKey();
    upKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(Tetrimino::UP);
        }
        else {
            mTetrimino.UnsetControl(Tetrimino::UP);
        }
    };

    controller.AddInputActionForKey(upKeyAction);

    ButtonAction downKeyAction;
    downKeyAction.key = GameController::DownKey();
    downKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(Tetrimino::DOWN);
        }
        else {
            mTetrimino.UnsetControl(Tetrimino::DOWN);
        }
    };

    controller.AddInputActionForKey(downKeyAction);

    mLevel.Init();
    mTetrimino.Init(mLevel);
}

void Tetris::Update(u_int32_t deltaTime) {
    mTetrimino.Update(deltaTime, mLevel);
    mLevel.Update(deltaTime);
}

void Tetris::Draw(Screen &screen) {
    mTetrimino.Draw(screen);
    mLevel.Draw(screen);
}

const std::string &Tetris::GetName() const {
     static std::string name = "Tetris";
     return name;
}


void Tetris::Reset() {}