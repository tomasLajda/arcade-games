//
// Created by ja on 7/2/24.
//

#ifndef ARCADE_GAMES_BOUNDARYEDGE_H
#define ARCADE_GAMES_BOUNDARYEDGE_H

#include "../../utils/vec2D.h"
#include "../../shapes/line2D.h"

enum EdgeType {
    BOTTOM_EDGE = 0,
    TOP_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    NUM_EDGES
};

static const Vec2D UP_DIR = {0, -1};
static const Vec2D DOWN_DIR = {0, 1};
static const Vec2D LEFT_DIR = {-1, 0};
static const Vec2D RIGHT_DIR = {1, 0};

class BoundaryEdge {
public:
    Vec2D normal;
    Line2D edge;
};


#endif//ARCADE_GAMES_BOUNDARYEDGE_H
