//
// Created by ja on 7/20/24.
//

#include "block.h"


Block::Block(): mOutlineColor(Color::White()), mFillColor(Color::White()) {}

void Block::Init(const AARectangle &rect, const Color &outlineColor, const Color &fillColor) {
    Excluder::Init(rect);
    
    mOutlineColor = outlineColor;
    mFillColor = fillColor;
}

void Block::Draw(Screen &screen) {
    screen.Draw(Excluder::GetAARectangle(), mOutlineColor, true, mFillColor);
}