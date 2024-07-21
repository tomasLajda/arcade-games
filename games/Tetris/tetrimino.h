//
// Created by ja on 7/20/24.
//

#ifndef ARCADE_GAMES_TETRIMINO_H
#define ARCADE_GAMES_TETRIMINO_H

#include "block.h"
#include "tetriminoTemplate.h"

enum TetriminoControl {
    UP = 0b1,
    LEFT = 0b10,
    RIGHT = 0b100,
    DOWN = 0b1000
};

class Tetrimino {
public:
    void Init();
    void Update(uint32_t deltaTime);
    void Draw(Screen &screen);

    inline void SetControl(TetriminoControl control) {mControl |= control;}
    inline void UnsetControl(TetriminoControl control) {mControl &= ~control;}
    inline void ResetControl() {mControl = 0;}

private:
    TetriminoTemplate mTemplate;
    std::vector<BlockT> mBlocks;
    uint32_t mUpdateCounter = 0;
    uint32_t mUpdateSpeed = 500;
    uint32_t mControl;
};


#endif//ARCADE_GAMES_TETRIMINO_H
