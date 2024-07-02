//
// Created by ja on 7/1/24.
//

#ifndef ARCADE_GAMES_INPUTCONTROLLER_H
#define ARCADE_GAMES_INPUTCONTROLLER_H

#include "inputAction.h"

class GameController;

class InputController {
public:
    InputController();
    void Init(InputAction quitAction);
    void Update(uint32_t deltaTime);

    void SetGameController(GameController *controller);

private:
    InputAction mQuit;
    GameController *mnoptrCurrentController;
};


#endif//ARCADE_GAMES_INPUTCONTROLLER_H
