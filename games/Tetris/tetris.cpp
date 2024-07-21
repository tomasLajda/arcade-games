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
            mTetrimino.SetControl(TetriminoControl::LEFT);
        }
        else {
            mTetrimino.UnsetControl(TetriminoControl::LEFT);
        }
    };

    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(TetriminoControl::RIGHT);
        }
        else {
            mTetrimino.UnsetControl(TetriminoControl::RIGHT);
        }
    };

    controller.AddInputActionForKey(rightKeyAction);

    ButtonAction upKeyAction;
    upKeyAction.key = GameController::UpKey();
    upKeyAction.action = [this](uint32_t deltaTime, InputState state) {
        if(GameController::IsPressed(state)) {
            mTetrimino.SetControl(TetriminoControl::UP);
        }
        else {
            mTetrimino.UnsetControl(TetriminoControl::UP);
        }
    };
}

 void Tetris::Update(u_int32_t deltaTime) {

}

 void Tetris::Draw(Screen &screen) {
    mTetrimino.Draw(screen);
}

 const std::string &Tetris::GetName() const {
     static std::string name = "Tetris";
     return name;
}


void Tetris::Reset() {}