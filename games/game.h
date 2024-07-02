//
// Created by ja on 7/1/24.
//

#ifndef ARCADE_GAMES_GAME_H
#define ARCADE_GAMES_GAME_H

#include <string>

class GameController;
class Screen;

class Game {
public:
    virtual ~Game() {}
    virtual void Init(GameController &controller) = 0;
    virtual void Update(u_int32_t deltaTime) = 0;
    virtual void Draw(Screen &screen) = 0;
    virtual std::string GetName() const = 0;
};


#endif//ARCADE_GAMES_GAME_H
