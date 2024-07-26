//
// Created by ja on 7/21/24.
//

#ifndef ARCADE_GAMES_TETRIMINOTEMPLATE_H
#define ARCADE_GAMES_TETRIMINOTEMPLATE_H

#include "../../graphics/color.h"
#include <cstddef>
#include <cstdint>

enum TetriminoShapes {
    I = 0,
    O,
    T,
    J,
    L,
    S,
    Z
};

enum RotationDir {
    LEFT_R = 0,
    RIGHT_R
};

class TetriminoTemplate {
public:
    void Init();
    void Rotate(RotationDir dir = LEFT_R);
    void SetColor();
    void SetShape();
    bool GetBlock(size_t r, size_t c) const;

    inline TetriminoShapes GetShape() const {return mShape;}
    inline Color GetFillColor() const {return mFillColor;}
    inline Color GetOutlineColor() const {return mOutlineColor;}
    inline bool IsInit() const {return mIsInit;};

private:
    TetriminoShapes mShape;
    bool mBlocks[3][3];
    Color mOutlineColor;
    Color mFillColor;
    bool mIsInit = false;
};


#endif//ARCADE_GAMES_TETRIMINOTEMPLATE_H
