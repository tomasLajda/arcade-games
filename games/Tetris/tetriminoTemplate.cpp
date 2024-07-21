//
// Created by ja on 7/21/24.
//

#include "tetriminoTemplate.h"
#include <cstdlib>

void TetriminoTemplate::Init() {
    mShape = static_cast<TetriminoShapes>(rand() % 7);

    switch (mShape) {
        case I:
            mBlocks[0][0] = true;
            mBlocks[0][1] = true;
            mBlocks[0][2] = true;
            mBlocks[1][0] = false;
            mBlocks[1][1] = false;
            mBlocks[1][2] = false;
            mBlocks[2][0] = false;
            mBlocks[2][1] = false;
            mBlocks[2][2] = false;
            break;
        case O:
            mBlocks[0][0] = true;
            mBlocks[0][1] = true;
            mBlocks[0][2] = false;
            mBlocks[1][0] = true;
            mBlocks[1][1] = true;
            mBlocks[1][2] = false;
            mBlocks[2][0] = false;
            mBlocks[2][1] = false;
            mBlocks[2][2] = false;
            break;
        case T:
            mBlocks[0][0] = true;
            mBlocks[0][1] = true;
            mBlocks[0][2] = true;
            mBlocks[1][0] = false;
            mBlocks[1][1] = true;
            mBlocks[1][2] = false;
            mBlocks[2][0] = false;
            mBlocks[2][1] = false;
            mBlocks[2][2] = false;
            break;
        case J:
            mBlocks[0][0] = true;
            mBlocks[0][1] = true;
            mBlocks[0][2] = true;
            mBlocks[1][0] = false;
            mBlocks[1][1] = false;
            mBlocks[1][2] = true;
            mBlocks[2][0] = false;
            mBlocks[2][1] = false;
            mBlocks[2][2] = false;
            break;
        case L:
            mBlocks[0][0] = true;
            mBlocks[0][1] = true;
            mBlocks[0][2] = true;
            mBlocks[1][0] = true;
            mBlocks[1][1] = false;
            mBlocks[1][2] = false;
            mBlocks[2][0] = false;
            mBlocks[2][1] = false;
            mBlocks[2][2] = false;
            break;
        case S:
            mBlocks[0][0] = false;
            mBlocks[0][1] = true;
            mBlocks[0][2] = true;
            mBlocks[1][0] = true;
            mBlocks[1][1] = true;
            mBlocks[1][2] = false;
            mBlocks[2][0] = false;
            mBlocks[2][1] = false;
            mBlocks[2][2] = false;
            break;
        case Z:
            mBlocks[0][0] = true;
            mBlocks[0][1] = true;
            mBlocks[0][2] = false;
            mBlocks[1][0] = false;
            mBlocks[1][1] = true;
            mBlocks[1][2] = true;
            mBlocks[2][0] = false;
            mBlocks[2][1] = false;
            mBlocks[2][2] = false;
            break;
    }
}

void TetriminoTemplate::Rotate() {
    if(mShape == O) {
        return;
    }

    if(mShape == I) {
        if(mBlocks[0][2]) {
            mBlocks[0][1] = false;
            mBlocks[0][2] = false;
            mBlocks[1][0] = true;
            mBlocks[2][0] = true;
        }
        else {
            mBlocks[1][0] = false;
            mBlocks[2][0] = false;
            mBlocks[0][1] = true;
            mBlocks[0][2] = true;
        }

        return;
    }

    bool temp[3][3];

    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            temp[r][c] = mBlocks[r][c];
        }
    }

    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            mBlocks[r][c] = temp[2-c][r];
        }
    }
}