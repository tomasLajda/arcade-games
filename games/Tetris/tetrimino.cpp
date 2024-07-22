//
// Created by ja on 7/20/24.
//

#include "tetrimino.h"
#include <cstdlib>

void Tetrimino::Init() {
    mTemplate.Init();
    mPlacement = Vec2D(14 * BlockT::BLOCK_SIZE, 15 * BlockT::BLOCK_SIZE);
    mControl = 0;
    mUpdateCounter = 0;
    mUpdateCounter = 0;
    mUpdateSpeed = 800;
    PlaceBlocks();
}

void Tetrimino::Update(uint32_t deltaTime) {
    mUpdateCounter += deltaTime;
    mControlSpeed += deltaTime;

    if(mControlSpeed >= 250) {
        switch (mControl) {
            case TetriminoControl::LEFT:
                for(auto &block : mBlocks) {
                    block.MoveBy(Vec2D(-BlockT::BLOCK_SIZE, 0));
                }
                mPlacement -= Vec2D(BlockT::BLOCK_SIZE, 0);
                break;
            case TetriminoControl::RIGHT:
                for(auto &block : mBlocks) {
                    block.MoveBy(Vec2D(BlockT::BLOCK_SIZE, 0));
                }
                mPlacement += Vec2D(BlockT::BLOCK_SIZE, 0);
                break;
            case TetriminoControl::UP:
                mTemplate.Rotate();
                PlaceBlocks();
                break;
            case TetriminoControl::DOWN:
                for(auto &block : mBlocks) {
                    block.MoveBy(Vec2D(0, BlockT::BLOCK_SIZE));
                }
                mPlacement += Vec2D(0, BlockT::BLOCK_SIZE);
                mUpdateCounter = 0;
                break;
        }
        mControlSpeed = 0;
    }

    if(mUpdateCounter >= mUpdateSpeed) {
        mUpdateCounter = 0;
        for(auto &block : mBlocks) {
            block.MoveBy(Vec2D(0, block.BLOCK_SIZE));
        }
        mPlacement += Vec2D(0, BlockT::BLOCK_SIZE);
    }
}

void Tetrimino::Draw(Screen &screen) {
    for(auto &block : mBlocks) {
        block.Draw(screen);
    }
}

void Tetrimino::PlaceBlocks() {
    mBlocks.clear();
    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            if(mTemplate.GetBlock(r, c)) {
                BlockT block;
                block.Init(Vec2D(mPlacement.GetX() + r * BlockT::BLOCK_SIZE, mPlacement.GetY() + c * BlockT::BLOCK_SIZE), Color::Red(), Color::White());
                mBlocks.push_back(block);
            }
        }
    }
}