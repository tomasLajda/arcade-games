//
// Created by ja on 7/18/24.
//

#include "tetris.h"

#include "../../input/gameController.h"


 void Tetris::Init(GameController &controller) {
    controller.ClearAll();

    Reset();

    ButtonAction leftKeyAction;

    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state) {

    };
}

 void Tetris::Update(u_int32_t deltaTime) {

}

 void Tetris::Draw(Screen &screen) {

}

 const std::string &Tetris::GetName() const {
     static std::string name = "Tetris";
     return name;
}


void Tetris::Reset() {}