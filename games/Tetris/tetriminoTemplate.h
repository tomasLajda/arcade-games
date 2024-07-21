//
// Created by ja on 7/21/24.
//

#ifndef ARCADE_GAMES_TETRIMINOTEMPLATE_H
#define ARCADE_GAMES_TETRIMINOTEMPLATE_H

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

class TetriminoTemplate {
public:
    void Init();
    void Rotate();

    inline TetriminoShapes GetShape() const {return mShape;}

private:
    TetriminoShapes mShape;
    bool mBlocks[3][3];
};


#endif//ARCADE_GAMES_TETRIMINOTEMPLATE_H
