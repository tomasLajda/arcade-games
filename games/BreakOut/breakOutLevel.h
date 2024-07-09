//
// Created by ja on 7/8/24.
//

#ifndef ARCADE_GAMES_BREAKOUTLEVEL_H
#define ARCADE_GAMES_BREAKOUTLEVEL_H

#include <vector>
#include <cstdint>
#include "block.h"

class Screen;
class Ball;
class AARectangle;

class BreakOutLevel {
public:
    BreakOutLevel();
    void Init(const AARectangle &boundary);
    void Load(const std::vector<Block> &blocks);
    void Update(uint32_t deltaTime, Ball &ball);
    void Draw(Screen &screen);

    bool IsLevelComplete() const;
    static std::vector<BreakOutLevel> LoadLevelsFromFile(const std::string &filePath);

private:
    void CreateDefaultLevel(const AARectangle &boundary);

private:
    std::vector<Block> mBlocks;

    static const int BLOCK_WIDTH = 16;
    static const int BLOCK_HEIGHT = 8;
};


#endif//ARCADE_GAMES_BREAKOUTLEVEL_H
