//
// Created by ja on 7/2/24.
//

#ifndef ARCADE_GAMES_BREAKOUT_H
#define ARCADE_GAMES_BREAKOUT_H

#include "../game.h"
#include <iostream>

class BreakOut: public Game {
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(u_int32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() const override;
private:

};


#endif//ARCADE_GAMES_BREAKOUT_H
