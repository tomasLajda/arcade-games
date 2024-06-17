//
// Created by ja on 6/13/24.
//

#ifndef ARCADE_GAMES_STAR2D_H
#define ARCADE_GAMES_STAR2D_H

#include "../utils/vec2D.h"
#include "line2D.h"
#include <cstdint>
#include <vector>

class Star2D {
public:
    Star2D(): Star2D(0, 0, Vec2D(0, 0), 0) {};
    Star2D(uint32_t rad0, uint32_t rad1, float x, float y, uint32_t spikes): Star2D(rad0, rad1, Vec2D(x , y), spikes) {};
    Star2D(uint32_t rad0, uint32_t rad1, Vec2D center, uint32_t spikes): mRad0(rad0), mRad1(rad1), mCenter(center), mSpikes(spikes) {};

    inline const uint32_t &GetRad0() const {return  mRad0;}
    inline const uint32_t &GetRad1() const {return  mRad1;}
    inline const uint32_t &GetSpikes() const {return  mSpikes;}

    inline void SetRad0(uint32_t rad) {mRad0 = rad;}
    inline void SetRad1(uint32_t rad) {mRad1 = rad;}
    inline void SetSpikes(uint32_t spikes) {mSpikes = spikes;}

private:
    uint32_t mRad0, mRad1, mSpikes;
    Vec2D mCenter;
    std::vector<Vec2D> mEdges;
};

#endif//ARCADE_GAMES_STAR2D_H
