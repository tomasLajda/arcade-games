//
// Created by ja on 7/18/24.
//

#include "tetris.h"

void Tetris::Init(GameController &controller) {
    srand(time(nullptr));

    controller.ClearAll();

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

    ButtonAction actionKey;
    actionKey.key = GameController::ActionKey();
    actionKey.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(Tetrimino::ACTION);
        }
        else {
            mTetrimino.UnsetControl(Tetrimino::ACTION);
        }
    };

    controller.AddInputActionForKey(actionKey);

    ButtonAction cancelKey;
    cancelKey.key = GameController::CancelKey();
    cancelKey.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(Tetrimino::CANCEL);
        }
        else {
            mTetrimino.UnsetControl(Tetrimino::CANCEL);
        }
    };

    controller.AddInputActionForKey(cancelKey);

    Reset();
}

void Tetris::Update(u_int32_t deltaTime) {
    if(mState == IN_SERVE) {
        if(mTetrimino.GetControl() == Tetrimino::ACTION) {
            mState = IN_PLAY;
        }
    }

    if(mState == IN_PLAY) {
        mTetrimino.Update(deltaTime, mLevel);
    }

    if(mState == GAME_OVER) {
        if(mTetrimino.GetControl() == Tetrimino::ACTION) {
            mState = IN_SERVE;
            Reset();
        }
    }


    if(mLevel.GameOver()) {
        mState = GAME_OVER;
    }
}

void Tetris::Draw(Screen &screen) {
    mTetrimino.Draw(screen);
    mLevel.Draw(screen);
}

const std::string &Tetris::GetName() const {
     static std::string name = "Tetris";
     return name;
}


void Tetris::Reset() {
    mLevel.Init();
    mTetrimino.Init(mLevel);
}