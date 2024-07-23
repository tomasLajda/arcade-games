//
// Created by ja on 7/22/24.
//

#ifndef ARCADE_GAMES_TETRISLEVEL_H
#define ARCADE_GAMES_TETRISLEVEL_H

#include <cstdint>
#include "blockT.h"

struct Barrier {
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
};

class TetrisLevel {
public:
    void Init();
    void Update(uint32_t deltaTime);
    void Draw(Screen &screen);
    bool IsColliding(const BlockT &block) const;
    void AddPlayingBlock(BlockT &block);
    void ClearRow();

    inline Barrier GetBarrier() const {return mBarrier;}

private:
    uint32_t mLevel;
    uint32_t mScore;
    std::vector<BlockT> mPlayingBlocks;
    std::vector<BlockT> mLevelBlocks;
    Barrier mBarrier;
};


#endif//ARCADE_GAMES_TETRISLEVEL_H
