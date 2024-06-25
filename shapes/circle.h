//
// Created by ja on 6/24/24.
//

#ifndef ARCADE_GAMES_CIRCLE_H
#define ARCADE_GAMES_CIRCLE_H

#include "shape.h"

class Circle: public Shape {
public:
    Circle();
    Circle(const Vec2D &center, float radius);

    virtual Vec2D GetCenterPoint() const override {return mPoints[0];}
    inline float GetRadius() const {return mRadius;}
    inline void SetRadius(float radius) {mRadius = radius;}
    void MoveTo(const Vec2D &position) {mPoints[0] = position;}

    bool Intersects(const Circle &otherCircle) const;
    bool ContainsPoints(const Vec2D &point) const;


private:
    float mRadius;
};


#endif//ARCADE_GAMES_CIRCLE_H
