//
// Created by ja on 6/13/24.
//

#include "star2D.h"

Star2D::Star2D(): Star2D(1, 2, Vec2D(0, 0), 5) {}

Star2D::Star2D(uint32_t rad0, uint32_t rad1, float x, float y, uint32_t spikes): Star2D(rad0, rad1, Vec2D(x , y), spikes) {}

Star2D::Star2D(uint32_t rad0, uint32_t rad1, Vec2D center, uint32_t spikes): mRad0(rad0), mRad1(rad1), mCenter(center), mSpikes(spikes) {
    Vec2D vec0 = Vec2D(mCenter.GetX(), mCenter.GetY() - rad0);
    Vec2D vec1 = Vec2D(mCenter.GetX(), mCenter.GetY() - rad1);
    float angle = (PI * 2) / (float)mSpikes;

    vec0.Rotate(angle/2, mCenter);

    Line2D edge;
    mEdges.clear();
    for (int i = 0; i < mSpikes * 2; ++i) {
        edge.SetP0(vec0);
        edge.SetP1(vec1);
        mEdges.push_back(edge);

        if(i % 2) {
            vec0.Rotate(angle, mCenter);
        }
        else {
            vec1.Rotate(angle, mCenter);
        }
    }
}