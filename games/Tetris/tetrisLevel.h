//
// Created by ja on 7/22/24.
//

#ifndef ARCADE_GAMES_TETRISLEVEL_H
#define ARCADE_GAMES_TETRISLEVEL_H

#include <cstdint>
#include "blockT.h"

class TetrisLevel {
public:
    void Init();
    void Draw(Screen &screen);
    bool IsColliding(const BlockT &block) const;
    void AddPlayingBlock(BlockT &block);
    void ClearRows();
    void UpdateLevel();
    void DisplayScoreLevel(Screen &screen);
    bool GameOver();

    inline const AARectangle GetPlayingField() {return mPlayingField;}
    inline void AddFastDropPoint() {++mFastDropPoints;}
    inline uint32_t GetGameSpeed() {return mGameSpeed;}

private:
    std::array<std::vector<BlockT>, 20> mPlacedBlocks;
    AARectangle mPlayingField;
    uint32_t mLevel = 0;
    uint32_t mScore;
    uint32_t mGameSpeed;
    uint8_t mRowsBroken;
    uint32_t mFastDropPoints;
};


#endif//ARCADE_GAMES_TETRISLEVEL_H
