//
// Created by ja on 7/20/24.
//

#include "blockT.h"


BlockT::BlockT(): mOutlineColor(Color::White()), mFillColor(Color::White()), mRect(Vec2D::Zero, BlockT::BLOCK_SIZE, BlockT::BLOCK_SIZE) {}

void BlockT::Init(const Vec2D placement, const Color &outlineColor, const Color &fillColor) {
    AARectangle rect(placement, BLOCK_SIZE, BLOCK_SIZE);
    mRect = rect;

    mOutlineColor = outlineColor;
    mFillColor = fillColor;
}

void BlockT::Draw(Screen &screen) {
    screen.Draw(mRect, mOutlineColor, true, mFillColor);
}

void BlockT::MoveBy(const Vec2D &DeltaOffset) {
    mRect.MoveBy(DeltaOffset);
}
