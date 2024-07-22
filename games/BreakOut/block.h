//
// Created by ja on 7/3/24.
//

#ifndef ARCADE_GAMES_BLOCKT_H
#define ARCADE_GAMES_BLOCK_H

#include "../../graphics/color.h"
#include "excluder.h"

class Ball;
class Screen;
struct BoundaryEdge;

class Block: public Excluder {
public:
    Block();
    void Init(const AARectangle &rect, int hp, const Color &outlineColor, const Color &fillColor);
    void Draw(Screen &screen);
    void Bounce(Ball &ball, const BoundaryEdge &edge);

    void ReduceHP();
    inline int GetHp() const {return mHp;}
    inline bool IsDestroyed() const {return mHp == 0;}
    inline const Color &GetOutlineColor() const {return mOutlineColor;}
    inline const Color &GetFillColor() const {return mFillColor;}


public:
    static const int UNBREAKABLE = -1;

private:
    Color mOutlineColor;
    Color mFillColor;

    int mHp;
};


#endif//ARCADE_GAMES_BLOCKT_H
