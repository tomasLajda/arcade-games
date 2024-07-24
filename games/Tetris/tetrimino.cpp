//
// Created by ja on 7/20/24.
//

#include "tetrimino.h"

void Tetrimino::Init(TetrisLevel &level) {
    mTemplate.Init();
    mPlacement = Vec2D(13 * BlockT::BLOCK_SIZE, 14 * BlockT::BLOCK_SIZE);
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
                block.Init(Vec2D(tempPlacement.GetX() + c * BlockT::BLOCK_SIZE, tempPlacement.GetY() + r * BlockT::BLOCK_SIZE), Color::Red(), Color::White());
                if(level.IsColliding(block)) {
                    return false;
                }
                tempBlocks.push_back(block);
            }
        }
    }

    if(tempTemplate.GetShape() == I) {
        BlockT block;
        if(tempTemplate.GetBlock(0, 0)) {
            block.Init(Vec2D(tempPlacement.GetX() + 3 * BlockT::BLOCK_SIZE, tempPlacement.GetY() + 0 * BlockT::BLOCK_SIZE), Color::Red(), Color::White());
        }
        else {
            block.Init(Vec2D(tempPlacement.GetX() + 2 * BlockT::BLOCK_SIZE, tempPlacement.GetY() + 3 * BlockT::BLOCK_SIZE), Color::Red(), Color::White());
        }
        if(level.IsColliding(block)) {
            return false;
        }
        tempBlocks.push_back(block);
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