//
// Created by ja on 7/22/24.
//

#include "tetrisLevel.h"
#include "../../shapes/line2D.h"

void TetrisLevel::Init() {
    mLevel = 0;
    mScore = 0;
    mGameSpeed = 660;

    for(auto &row : mPlacedBlocks) {
        row.clear();
    }

    float top = BlockT::BLOCK_SIZE * 13 - 1;
    float left = BlockT::BLOCK_SIZE * 9 - 1;
    float right = App::Singleton().Width() - BlockT::BLOCK_SIZE * 9;
    float bottom = App::Singleton().Height() - BlockT::BLOCK_SIZE * 2;

    AARectangle rect(Vec2D(left, top), Vec2D(right, bottom));
    mPlayingField = rect;
}

void TetrisLevel::Draw(Screen &screen) {
    for(auto &row : mPlacedBlocks) {
        for(auto &block : row) {
            block.Draw(screen);
        }
    }

    screen.Draw(mPlayingField, Color::DarkGrey(), false);
    DisplayScore(screen);
}

bool TetrisLevel::IsColliding(const BlockT &block) const {
    Vec2D topLeftBlock = block.GetAARectangle().GetTopLeftPoint();
    Vec2D topLeftPlaying = mPlayingField.GetTopLeftPoint();
    Vec2D bottomRightPlaying = mPlayingField.GetBottomRightPoint();

    if((bottomRightPlaying.GetY() <= topLeftBlock.GetY() || topLeftPlaying.GetX() >= topLeftBlock.GetX() || bottomRightPlaying.GetX() <= topLeftBlock.GetX())){
        return true;
    }

    int row = (topLeftBlock.GetY() - topLeftPlaying.GetY()) / BlockT::BLOCK_SIZE - 1;

    if(row < 0) return false;

    for(auto &placedBlock : mPlacedBlocks[row]) {
        if(placedBlock.GetAARectangle().Intersects(block.GetAARectangle())) {
            return true;
        }
    }

    return false;
}

void TetrisLevel::AddPlayingBlock(BlockT &block) {
    int row = (block.GetAARectangle().GetTopLeftPoint().GetY() - mPlayingField.GetTopLeftPoint().GetY()) / BlockT::BLOCK_SIZE - 1;
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
            for(auto &block : mPlacedBlocks[i]) {
                block.MoveBy(Vec2D(0, BlockT::BLOCK_SIZE));
            }
        }
    }

    switch (clearedRows.size()) {
        case 1:
            mScore += 40 * (mLevel + 1);
            break;
        case 2:
            mScore += 100 * (mLevel + 1);
            break;
        case 3:
            mScore += 300 * (mLevel + 1);
            break;
        case 4:
            mScore += 1200 * (mLevel + 1);
            break;
    }

    mRowsBroken += clearedRows.size();
    mScore += mFastDropPoints;

    if(mRowsBroken >= 10) {
        mRowsBroken -= 10;
        UpdateLevel();
    }
}

void TetrisLevel::UpdateLevel() {
    ++mLevel;
    if(mLevel < 10 || mLevel == 13 || mLevel == 16 || mLevel == 19) {
        mGameSpeed -= 60;
    }
}

void TetrisLevel::DisplayScore(Screen &screen) {
    std::string score = "Score: " + std::to_string(mScore);

    screen.DrawText(score, Color::White(), Vec2D(2 * BlockT::BLOCK_SIZE, 6 * BlockT::BLOCK_SIZE));

    std::string level = "Level: " + std::to_string(mLevel);

    screen.DrawText(level, Color::White(), Vec2D(2 * BlockT::BLOCK_SIZE, 2 * BlockT::BLOCK_SIZE));
}
