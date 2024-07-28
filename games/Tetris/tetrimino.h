//
// Created by ja on 7/20/24.
//

#ifndef ARCADE_GAMES_TETRIMINO_H
#define ARCADE_GAMES_TETRIMINO_H

#include "blockT.h"
#include "tetriminoTemplate.h"
#include "tetrisLevel.h"

class Tetrimino {
public:
    enum TetriminoControl {
        UP = 0b1,
        LEFT = 0b10,
        RIGHT = 0b100,
        DOWN = 0b1000,
        ACTION = 0b10000,
        CANCEL = 0b100000
    };

    void Init(TetrisLevel &level);
    void Update(uint32_t deltaTime, TetrisLevel &level);
    void Draw(Screen &screen);
    bool Movement(TetrisLevel &level, Vec2D movement, bool isRotating = false, RotationDir dir = LEFT_R);
    void PlaceBlockToLevel(TetrisLevel &level);
    std::vector<BlockT> GenNextBlocks();

    inline void SetControl(TetriminoControl control) {mControl |= control;}
    inline void UnsetControl(TetriminoControl control) {mControl &= ~control;}
    inline uint32_t GetControl() {return mControl;}

private:
    TetriminoTemplate mNextTemplate;
    TetriminoTemplate mTemplate;
    std::vector<BlockT> mBlocks;
    Vec2D mPlacement;
    uint32_t mUpdateCounter;
    uint32_t mControlSpeed;
    uint32_t mControl;
};


#endif//ARCADE_GAMES_TETRIMINO_H
