//
// Created by ja on 7/20/24.
//

#include "tetrimino.h"

void Tetrimino::Init(TetrisLevel &level) {
    if (!mNextTemplate.IsInit()) {
        mTemplate.Init();
        mNextTemplate.Init();
    } else {
        mTemplate = mNextTemplate;
        mNextTemplate.Init();
    }

    mPlacement = level.GetPlayingField().GetTopLeftPoint() + Vec2D(1 + BlockT::BLOCK_SIZE * 4, 1);

    mControl = 0;
    mUpdateCounter = 0;
    Movement(level, Vec2D::Zero);
}

void Tetrimino::Update(uint32_t deltaTime, TetrisLevel &level) {
    mUpdateCounter += deltaTime;
    mControlSpeed += deltaTime;

    if(mControl == TetriminoControl::DOWN && mControlSpeed >= 60) {
        if(!Movement(level, Vec2D(0, BlockT::BLOCK_SIZE))) {
            PlaceBlockToLevel(level);
        }
            level.AddFastDropPoint();

        mUpdateCounter = 0;
        mControlSpeed = 0;
    }

    if(mControl == TetriminoControl::LEFT && mControlSpeed >= 150) {
        Movement(level, Vec2D(-BlockT::BLOCK_SIZE, 0));
        mControlSpeed = 0;
    }

    if(mControl == TetriminoControl::RIGHT && mControlSpeed >= 150) {
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

    if(mUpdateCounter >= level.GetGameSpeed()) {
        mUpdateCounter = 0;
        if(!Movement(level, Vec2D(0, BlockT::BLOCK_SIZE))) {
            PlaceBlockToLevel(level);
        }
    }
}

void Tetrimino::Draw(Screen &screen) {
    for(auto &block : mBlocks) {
        block.Draw(screen);
    }

    std::vector<BlockT> nextBlocks = GenNextBlocks();
    for(auto &block : nextBlocks) {
        block.Draw(screen);
    }

    screen.DrawText("Next:", Color::White(), Vec2D(20 * BlockT::BLOCK_SIZE, 2 * BlockT::BLOCK_SIZE));
}

std::vector<BlockT> Tetrimino::GenNextBlocks() {
    std::vector<BlockT> nextBlocks;

    for (size_t r = 0; r < 3; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            if(mNextTemplate.GetBlock(r, c)) {
                BlockT block;
                block.Init(Vec2D( 21 * BlockT::BLOCK_SIZE + c * BlockT::BLOCK_SIZE,  6 * BlockT::BLOCK_SIZE + r * BlockT::BLOCK_SIZE), mNextTemplate.GetOutlineColor(), mNextTemplate.GetFillColor());
                nextBlocks.push_back(block);
            }
        }
    }

    if(mNextTemplate.GetShape() == I) {
        BlockT block;
        block.Init(Vec2D(21 * BlockT::BLOCK_SIZE + 3 * BlockT::BLOCK_SIZE, 6 * BlockT::BLOCK_SIZE), mNextTemplate.GetOutlineColor(), mNextTemplate.GetFillColor());
        nextBlocks.push_back(block);
    }

    return nextBlocks;
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
            block.Init(Vec2D(tempPlacement.GetX() + 3 * BlockT::BLOCK_SIZE, tempPlacement.GetY()), mTemplate.GetOutlineColor(), mTemplate.GetFillColor());
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

    level.ClearRows();
    mBlocks.clear();
    Init(level);
}