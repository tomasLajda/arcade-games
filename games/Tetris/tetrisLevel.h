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
    void Update(uint32_t deltaTime);
    void Draw(Screen &screen);
    bool IsColliding(const BlockT &block) const;
    void AddPlayingBlock(BlockT &block);
    void ClearRows();

private:
    uint32_t mLevel;
    uint32_t mScore;
    std::array<std::vector<BlockT>, 20> mPlacedBlocks;
    AARectangle mPlayingField;
};


#endif//ARCADE_GAMES_TETRISLEVEL_H
