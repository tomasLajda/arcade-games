//
// Created by ja on 7/20/24.
//

#ifndef ARCADE_GAMES_TETRIMINO_H
#define ARCADE_GAMES_TETRIMINO_H

#include "block.h"

enum TetriminoShapes {
    I = 0,
    O,
    T,
    J,
    L,
    S,
    Z
};


class Tetrimino {
public:
    Tetrimino();

private:
    TetriminoShapes mShape;
    std::vector<Block> mBlocks;
};


#endif//ARCADE_GAMES_TETRIMINO_H
