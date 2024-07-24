//
// Created by ja on 7/22/24.
//

#include "tetrisLevel.h"

void TetrisLevel::Init() {
    mLevel = 0;
    mScore = 0;
    for(auto &row : mPlacedBlocks) {
        row.clear();
    }
    mLevelBlocks.clear();
    mBarrier.bottom = App::Singleton().Height() - BlockT::BLOCK_SIZE * 2;
    mBarrier.top = BlockT::BLOCK_SIZE * 13;
    mBarrier.left = BlockT::BLOCK_SIZE * 8;
    mBarrier.right = App::Singleton().Width() - BlockT::BLOCK_SIZE * 9;

    for(uint32_t r = 0; r < App::Singleton().Height()/BlockT::BLOCK_SIZE; ++r) {
        for (uint32_t c = 0; c < App::Singleton().Width()/BlockT::BLOCK_SIZE; ++c) {
            BlockT block;
            block.Init(Vec2D(c * BlockT::BLOCK_SIZE, r * BlockT::BLOCK_SIZE), Color::LightGrey(), Color::DarkGrey());
            const Vec2D topLeftCorner = block.GetAARectangle().GetTopLeftPoint();
            if(mBarrier.bottom <= topLeftCorner.GetY() || mBarrier.top >= topLeftCorner.GetY() || mBarrier.left >= topLeftCorner.GetX() || mBarrier.right <= topLeftCorner.GetX()){
                mLevelBlocks.push_back(block);
            }
        }
    }
}

void TetrisLevel::Update(uint32_t deltaTime) {
    ClearRows();
}

void TetrisLevel::Draw(Screen &screen) {
    for(auto &row : mPlacedBlocks) {
        for(auto &block : row) {
            block.Draw(screen);
        }
    }

    for(auto &block : mLevelBlocks) {
        block.Draw(screen);
    }
}

bool TetrisLevel::IsColliding(const BlockT &block) const {
    Vec2D topLeftPoint = block.GetAARectangle().GetTopLeftPoint();
    if((mBarrier.bottom <= topLeftPoint.GetY() || mBarrier.left >= topLeftPoint.GetX() || mBarrier.right <= topLeftPoint.GetX())){
        return true;
    }

    int row = (topLeftPoint.GetY() - mBarrier.top) / BlockT::BLOCK_SIZE - 1;

    for(auto &placedBlock : mPlacedBlocks[row]) {
        if(placedBlock.GetAARectangle().Intersects(block.GetAARectangle())) {
            return true;
        }
    }

    return false;
}

void TetrisLevel::AddPlayingBlock(BlockT &block) {
    int row = (block.GetAARectangle().GetTopLeftPoint().GetY() - mBarrier.top) / BlockT::BLOCK_SIZE - 1;
    mPlacedBlocks[row].push_back(block);
}

void TetrisLevel::ClearRows() {
    std::vector<int> clearedRows;
    int rowIndex = 0;
    for(auto &row : mPlacedBlocks) {
        if(row.size() == 10) {
            row.clear();
            clearedRows.push_back(rowIndex);
        }
        rowIndex++;
    }

    for(int &clearedRow : clearedRows) {
        for(int i = clearedRow; i > 0; --i) {
            mPlacedBlocks[i] = mPlacedBlocks[i-1];
        }
    }
}