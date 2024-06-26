//
// Created by ja on 6/21/24.
//

#ifndef ARCADE_GAMES_SHAPE_H
#define ARCADE_GAMES_SHAPE_H

#include "../utils/vec2D.h"
#include <vector>

class Shape {
public:
    virtual Vec2D GetCenterPoint() const = 0;
    virtual bool ContainsPoint(const Vec2D &point) const = 0;
    virtual ~Shape() {}
    inline virtual std::vector<Vec2D> GetPoints() const {return mPoints;}
    void MoveBy(const Vec2D &deltaOffset);

protected:
    std::vector<Vec2D> mPoints;
};


#endif//ARCADE_GAMES_SHAPE_H
