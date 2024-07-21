//
// Created by ja on 7/20/24.
//

#ifndef ARCADE_GAMES_BLOCK_H
#define ARCADE_GAMES_BLOCK_H

#include "../../graphics/color.h"
#include "../../graphics/screen.h"
#include "../../shapes/AARectangle.h"
#include "../game-assets/excluder.h"
#include "../../app/app.h"

class BlockT: public Excluder {
public:
    BlockT();
    void Init(const Vec2D placement, const Color &outlineColor, const Color &fillColor);
    void Draw(Screen &screen);
    void Rotate(float Angle);

    inline const Color &GetOutlineColor() const {return mOutlineColor;}
    inline const Color &GetFillColor() const {return mFillColor;}

public:
    const uint32_t BLOCK_SIZE = App::Singleton().Width()/12;

private:
    Color mOutlineColor;
    Color mFillColor;
};


#endif//ARCADE_GAMES_BLOCK_H
