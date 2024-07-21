//
// Created by ja on 7/20/24.
//

#include "tetrimino.h"
#include <cstdlib>

void Tetrimino::Init() {
    mBlocks.clear();
    mTemplate.Init();

}

void Tetrimino::Update(uint32_t deltaTime) {
    mUpdateCounter += deltaTime;

    switch (mControl) {
        case TetriminoControl::LEFT:
            for(auto &block : mBlocks) {
                block.MoveBy(Vec2D(-block.BLOCK_SIZE, 0));
            }
            break;
        case TetriminoControl::RIGHT:
            for(auto &block : mBlocks) {
                block.MoveBy(Vec2D(block.BLOCK_SIZE, 0));
            }
            break;
        case TetriminoControl::UP:
            for(auto &block : mBlocks) {
//                block.GetAARectangle().
            }
            break;
        case TetriminoControl::DOWN:
            for(auto &block : mBlocks) {
                block.MoveBy(Vec2D(0, block.BLOCK_SIZE));
            }
            break;
    }

    if(mUpdateCounter >= mUpdateSpeed) {
        mUpdateCounter = 0;
        for(auto &block : mBlocks) {
            block.MoveBy(Vec2D(0, block.BLOCK_SIZE));
        }
    }

}

void Tetrimino::Draw(Screen &screen) {
    for(auto &block : mBlocks) {
        block.Draw(screen);
    }
}