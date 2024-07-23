//
// Created by ja on 7/20/24.
//

#include "tetrimino.h"

void Tetrimino::Init(TetrisLevel &level) {
    mTemplate.Init();
    mPlacement = Vec2D(14 * BlockT::BLOCK_SIZE, 14 * BlockT::BLOCK_SIZE);
    mControl = 0;
    mUpdateCounter = 0;
    mUpdateCounter = 0;
    mUpdateSpeed = 800;
    Movement(level, Vec2D::Zero, false);
}

void Tetrimino::Update(uint32_t deltaTime, TetrisLevel &level) {
    mUpdateCounter += deltaTime;
    mControlSpeed += deltaTime;

    if(mControlSpeed >= 250) {
        switch (mControl) {
            case TetriminoControl::LEFT:
                Movement(level, Vec2D(-BlockT::BLOCK_SIZE, 0), false);
                break;
            case TetriminoControl::RIGHT:
                Movement(level, Vec2D(BlockT::BLOCK_SIZE, 0), false);
                break;
            case TetriminoControl::UP:
                Movement(level, Vec2D::Zero, true);
                break;
            case TetriminoControl::DOWN:
                if(!Movement(level, Vec2D(0, BlockT::BLOCK_SIZE), false)) {
                    PlaceBlockToLevel(level);
                    level.ClearRow();
                }
                mUpdateCounter = 0;
                break;
        }

        if(mControl != 0) {
            mControlSpeed = 0;
        }
    }

    if(mUpdateCounter >= mUpdateSpeed) {
        mUpdateCounter = 0;
        if(!Movement(level, Vec2D(0, BlockT::BLOCK_SIZE), false)) {
            PlaceBlockToLevel(level);
            level.ClearRow();
        }
    }
}

void Tetrimino::Draw(Screen &screen) {
    for(auto &block : mBlocks) {
        block.Draw(screen);
    }
}

bool Tetrimino::Movement(TetrisLevel &level, Vec2D movement, bool isRotating) {
    TetriminoTemplate tempTemplate = mTemplate;
    std::vector<BlockT> tempBlocks;
    Vec2D tempPlacement = mPlacement + movement;

    if(isRotating) {
        tempTemplate.Rotate();
    }

    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            if(tempTemplate.GetBlock(r, c)) {
                BlockT block;
                block.Init(Vec2D(tempPlacement.GetX() + r * BlockT::BLOCK_SIZE, tempPlacement.GetY() + c * BlockT::BLOCK_SIZE), Color::Red(), Color::White());
                if(level.IsColliding(block)) {
                    return false;
                }
                tempBlocks.push_back(block);
            }
        }
    }

    mTemplate = tempTemplate;
    mBlocks = tempBlocks;
    mPlacement = tempPlacement;

    return true;
}

void Tetrimino::PlaceBlockToLevel(TetrisLevel &level) {
    for(auto &block : mBlocks) {
        level.AddPlayingBlock(block);
    }
    mBlocks.clear();
    Init(level);
}