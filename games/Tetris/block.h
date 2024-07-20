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

class Block: public Excluder {
public:
    Block();
    void Init(const AARectangle &rect, const Color &outlineColor, const Color &fillColor);
    void Draw(Screen &screen);

    inline const Color &GetOutlineColor() const {return mOutlineColor;}
    inline const Color &GetFillColor() const {return mFillColor;}
    inline uint32_t GetSize() const {return mSize;}

private:
    const uint32_t mSize = App::Singleton().Width()/12;
    Color mOutlineColor;
    Color mFillColor;
};


#endif//ARCADE_GAMES_BLOCK_H
