//
// Created by ja on 7/3/24.
//

#include "ball.h"
#include "boundaryEdge.h"
#include "../../graphics/screen.h"
#include "../../utils/utils.h"
#include "../../shapes/circle.h"

const float Ball::RADIUS = 5.0f;

Ball::Ball(): Ball(Vec2D::Zero, Ball::RADIUS) {}

Ball::Ball(const Vec2D &pos, float radius):mBoundingBox(pos - Vec2D(radius, radius), radius * 2.0f, radius * 2.0f), mVelocity(Vec2D::Zero) {}

void Ball::Update(u_int32_t deltaTime) {
    mBoundingBox.MoveBy(mVelocity * MillisecondsToSeconds(deltaTime));
}

void Ball::Draw(Screen &screen) {
    Circle circle = Circle(mBoundingBox.GetCenterPoint(), GetRadius());
    screen.Draw(circle, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge &edge, Vec2D &pointOnEdge, bool limitToEdge) {
    if(edge.normal == DOWN_DIR) {
        mBoundingBox.MoveTo(Vec2D(mBoundingBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
    }

    if(edge.normal == UP_DIR) {
        mBoundingBox.MoveTo(Vec2D(mBoundingBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBoundingBox.GetHeight()));
    }

    if(edge.normal == RIGHT_DIR) {
        mBoundingBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBoundingBox.GetTopLeftPoint().GetY()));
    }

    if(edge.normal == LEFT_DIR) {
        mBoundingBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() - mBoundingBox.GetWidth(), mBoundingBox.GetTopLeftPoint().GetY()));
    }

    pointOnEdge = edge.edge.ClosestPoint(mBoundingBox.GetCenterPoint(), limitToEdge);
}

void Ball::Bounce(const BoundaryEdge &edge) {
    Vec2D pointOnEdge;

    MakeFlushWithEdge(edge, pointOnEdge, false);

    mVelocity = mVelocity.Reflect(edge.normal);
}

void Ball::MoveTo(const Vec2D &point) {
    mBoundingBox.MoveTo(point - Vec2D(GetRadius(),GetRadius()));
}