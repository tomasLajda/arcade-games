//
// Created by ja on 7/3/24.
//

#ifndef ARCADE_GAMES_LEVELBOUNDARY_H
#define ARCADE_GAMES_LEVELBOUNDARY_H

#include "excluder.h"

class AARectangle;
class Ball;

class LevelBoundary {
public:
    LevelBoundary(){}
    LevelBoundary(const AARectangle &boundary);
    bool HasCollided(const Ball &ball, BoundaryEdge &edge);
    inline const AARectangle &GetAARectangle() const {return mIncluder.GetAARectangle();}

private:
    bool HasCollidedWithEdge(const Ball &ball, const BoundaryEdge &edge) const;
    Excluder mIncluder;
};


#endif//ARCADE_GAMES_LEVELBOUNDARY_H
