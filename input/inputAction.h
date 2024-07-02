//
// Created by ja on 7/1/24.
//

#ifndef ARCADE_GAMES_INPUTACTION_H
#define ARCADE_GAMES_INPUTACTION_H

#include <functional>
#include <cstdint>

using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;

using InputAction = std::function<void(uint32_t, InputState)>;

struct ButtonAction {
    InputKey key;
    InputAction action;
};

struct MousePosition {
    int32_t xPos, yPos;
};

using MouseMovedAction = std::function<void(const MousePosition &mousePosition)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition &position)>;

struct MouseButtonAction {
    MouseButton mouseButton;
    MouseInputAction mouseInputAction;
};


#endif//ARCADE_GAMES_INPUTACTION_H
