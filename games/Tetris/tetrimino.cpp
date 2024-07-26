//
// Created by ja on 7/20/24.
//

#include "tetrimino.h"

void Tetrimino::Init(TetrisLevel &level) {
    mTemplate.Init();
    mPlacement = level.GetPlayingField().GetTopLeftPoint() + Vec2D(1 + BlockT::BLOCK_SIZE * 4, 1);
    mControl = 0;
    mUpdateCounter = 0;
    mUpdateCounter = 0;
    mUpdateSpeed = level.GetGameSpeed();
    Movement(level, Vec2D::Zero);
}

void Tetrimino::Update(uint32_t deltaTime, TetrisLevel &level) {
    mUpdateCounter += deltaTime;
    mControlSpeed += deltaTime;

    if(mControl == TetriminoControl::DOWN && mControlSpeed >= 60) {
        if(!Movement(level, Vec2D(0, BlockT::BLOCK_SIZE))) {
            PlaceBlockToLevel(level);
            level.AddFastDropPoint();
            level.ClearRows();
        }
        mUpdateCounter = 0;
        mControlSpeed = 0;
    }

    if(mControl == TetriminoControl::LEFT && mControlSpeed >= 120) {
        Movement(level, Vec2D(-BlockT::BLOCK_SIZE, 0));
        mControlSpeed = 0;
    }

    if(mControl == TetriminoControl::RIGHT && mControlSpeed >= 140) {
        Movement(level, Vec2D(BlockT::BLOCK_SIZE, 0));
        mControlSpeed = 0;
    }


    if((mControl == TetriminoControl::UP || mControl == TetriminoControl::ACTION) && mControlSpeed >= 180) {
        Movement(level, Vec2D::Zero, true, LEFT_R);
        mControlSpeed = 0;
    }

    if(mControl == TetriminoControl::CANCEL && mControlSpeed >= 180) {
        Movement(level, Vec2D::Zero, true, RIGHT_R);
        mControlSpeed = 0;
    }

    if(mUpdateCounter >= mUpdateSpeed) {
        mUpdateCounter = 0;
        if(!Movement(level, Vec2D(0, BlockT::BLOCK_SIZE))) {
            PlaceBlockToLevel(level);
            level.ClearRows();
        }
    }
}

void Tetrimino::Draw(Screen &screen) {
    for(auto &block : mBlocks) {
        block.Draw(screen);
    }
}

bool Tetrimino::Movement(TetrisLevel &level, Vec2D movement, bool isRotating, RotationDir dir) {
    TetriminoTemplate tempTemplate = mTemplate;
    std::vector<BlockT> tempBlocks;
    Vec2D tempPlacement = mPlacement + movement;

    if(isRotating) {
        tempTemplate.Rotate(dir);
    }

    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            if(tempTemplate.GetBlock(r, c)) {
                BlockT block;
                block.Init(Vec2D(tempPlacement.GetX() + c * BlockT::BLOCK_SIZE, tempPlacement.GetY() + r * BlockT::BLOCK_SIZE), mTemplate.GetOutlineColor(), mTemplate.GetFillColor());
                if(level.IsColliding(block)) {
                    return false;
                }

                if(block.GetAARectangle().GetTopLeftPoint().GetY() > level.GetPlayingField().GetTopLeftPoint().GetY()){
                    tempBlocks.push_back(block);
                }
            }
        }
    }

    if(tempTemplate.GetShape() == I) {
        BlockT block;
        if(tempTemplate.GetBlock(0, 0)) {
            block.Init(Vec2D(tempPlacement.GetX() + 3 * BlockT::BLOCK_SIZE, tempPlacement.GetY() + 0 * BlockT::BLOCK_SIZE), mTemplate.GetOutlineColor(), mTemplate.GetFillColor());
        }
        else {
            block.Init(Vec2D(tempPlacement.GetX() + 2 * BlockT::BLOCK_SIZE, tempPlacement.GetY() - BlockT::BLOCK_SIZE), mTemplate.GetOutlineColor(), mTemplate.GetFillColor());
        }
        if(level.IsColliding(block)) {
            return false;
        }

        if(block.GetAARectangle().GetTopLeftPoint().GetY() > level.GetPlayingField().GetTopLeftPoint().GetY()){
            tempBlocks.push_back(block);
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