//
// Created by ja on 7/20/24.
//

#include "block.h"


BlockT::BlockT(): mOutlineColor(Color::White()), mFillColor(Color::White()) {}

void BlockT::Init(const Vec2D placement, const Color &outlineColor, const Color &fillColor) {
    AARectangle rect(placement, BLOCK_SIZE, BLOCK_SIZE);

    Excluder::Init(rect);
    
    mOutlineColor = outlineColor;
    mFillColor = fillColor;
}

void BlockT::Draw(Screen &screen) {
    screen.Draw(Excluder::GetAARectangle(), mOutlineColor, true, mFillColor);
}
