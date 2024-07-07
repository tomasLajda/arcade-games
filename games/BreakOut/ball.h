//
// Created by ja on 7/3/24.
//

#ifndef ARCADE_GAMES_BALL_H
#define ARCADE_GAMES_BALL_H

#include "../../shapes/AARectangle.h"
#include "../../shapes/AARectangle.h"

class Screen;
struct BoundaryEdge;

class Ball {
public:
    Ball();
    Ball(const Vec2D &pos, float radius);

    void Update(u_int32_t deltaTime);
    void Draw(Screen &screen);
    void MakeFlushWithEdge(const BoundaryEdge &edge, Vec2D &pointOnEdge, bool limitToEdge);
    void MoveTo(const Vec2D &point);
    void Bounce(const BoundaryEdge &edge);

    inline void Stop() {mVelocity = Vec2D::Zero;}
    inline const AARectangle GetBoundingRect() const {return mBoundingBox;}
    inline void SetVelocity(const Vec2D &vel) {mVelocity = vel;}
    inline Vec2D GetVelocity() const {return mVelocity;}
    inline float GetRadius() const {return mBoundingBox.GetWidth()/2.0f;}
    inline Vec2D GetPosition() const {return mBoundingBox.GetCenterPoint();}

private:
    AARectangle mBoundingBox;
    Vec2D mVelocity;

    static const float RADIUS;
};


#endif//ARCADE_GAMES_BALL_H
