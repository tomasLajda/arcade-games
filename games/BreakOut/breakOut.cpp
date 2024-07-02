//
// Created by ja on 7/2/24.
//

#include "breakOut.h"

void BreakOut::Init(GameController &controller) {
    std::cout << "Break out Game Init()" << std::endl;
}

void BreakOut::Update(u_int32_t deltaTime) {
    std::cout << "Break out Game Update()" << std::endl;
}

void BreakOut::Draw(Screen &screen) {
    std::cout << "Break out Game Draw()" << std::endl;
}

std::string BreakOut::GetName() const {
    return "Break Out!";
}
