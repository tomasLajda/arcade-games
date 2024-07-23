//
// Created by ja on 7/22/24.
//

#include "tetrisLevel.h"

void TetrisLevel::Init() {
    mLevel = 0;
    mScore = 0;
    mPlayingBlocks.clear();
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
//    for(auto &block : mPlayingBlocks) {
//        block.Update(deltaTime);
//    }
}

void TetrisLevel::Draw(Screen &screen) {
    for(auto &block : mPlayingBlocks) {
        block.Draw(screen);
    }

    for(auto &block : mLevelBlocks) {
        block.Draw(screen);
    }
}

bool TetrisLevel::IsColliding(const BlockT &block) const {
    Vec2D blockTopLeft = block.GetAARectangle().GetTopLeftPoint();
    if((mBarrier.bottom <= blockTopLeft.GetY() || mBarrier.left >= blockTopLeft.GetX() || mBarrier.right <= blockTopLeft.GetX())){
        return true;
    }

    for(auto &mPlayingBlock : mPlayingBlocks) {
        if(mPlayingBlock.GetAARectangle().Intersects(block.GetAARectangle())) {
            return true;
        }
    }

    return false;
}

void TetrisLevel::AddPlayingBlock(BlockT &block) {
    mPlayingBlocks.push_back(block);
}

void TetrisLevel::ClearRow() {
    std::array<int, 20> blockRowCount = {};

    for(auto &block : mPlayingBlocks) {
        int rowPosition = (block.GetAARectangle().GetTopLeftPoint().GetY() - mBarrier.top) / BlockT::BLOCK_SIZE - 1;
        ++blockRowCount[rowPosition];
    }

    for (int i = 0; i < blockRowCount.size(); ++i) {
        if(blockRowCount[i] == 10) {
            for(int j = 0; j < mPlayingBlocks.size(); ++j) {
                if((mPlayingBlocks[j].GetAARectangle().GetTopLeftPoint().GetY() - mBarrier.top) / BlockT::BLOCK_SIZE - 1 == i) {
                    mPlayingBlocks.erase(mPlayingBlocks.begin() + j);
                }
            }
        }
    }
}