//
// Created by ja on 7/2/24.
//

#ifndef ARCADE_GAMES_EXCLUDER_H
#define ARCADE_GAMES_EXCLUDER_H

#include "../../shapes/AARectangle.h"
#include "boundaryEdge.h"

class Excluder {
public:
    void Init(const AARectangle &rect, bool reverseNormals = false);
    bool HasCollided(const AARectangle &rect, BoundaryEdge &edge) const;
    Vec2D GetCollisionOffset(const AARectangle &rect) const;
    inline const AARectangle &GetAARectangle() const {return mAARect;}
    void MoveBy(const Vec2D &delta);
    void MoveTo(const Vec2D &point);
    const BoundaryEdge &GetEdge(EdgeType edge) const;

private:
    void SetupEdges();
    AARectangle mAARect;
    BoundaryEdge mEdges[NUM_EDGES];
    bool mReverseNormals;
};


#endif//ARCADE_GAMES_EXCLUDER_H
