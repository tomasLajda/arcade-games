//
// Created by ja on 7/3/24.
//

#include "paddle.h"
#include "../../graphics/screen.h"
#include "../../utils/utils.h"
#include "ball.h"
#include "boundaryEdge.h"
#include <cassert>

void Paddle::Init(const AARectangle &rect, const AARectangle &boundary) {
    Excluder::Init(rect);
    mBoundary = boundary;
    mDirection = 0;
}

void Paddle::Update(u_int32_t deltaTime, Ball &ball) {
    if(GetAARectangle().ContainsPoint(ball.GetPosition())) {
        Vec2D pointOnEdge;
        ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);

    }

    if(mDirection != 0) {
        Vec2D dir = mDirection == PaddleDirection::LEFT ? LEFT_DIR : RIGHT_DIR;
        if((mDirection & PaddleDirection::LEFT) == PaddleDirection::LEFT && (mDirection & PaddleDirection::RIGHT) == PaddleDirection::RIGHT) {
            dir = Vec2D::Zero;
        }

        Vec2D dx = dir * VELOCITY * MillisecondsToSeconds(deltaTime);

        MoveBy(dx);

        const AARectangle &aaRectangle = GetAARectangle();


        if(IsGreaterThanOrEqual(mBoundary.GetTopLeftPoint().GetX(), aaRectangle.GetTopLeftPoint().GetX())) {
            MoveTo(Vec2D(mBoundary.GetTopLeftPoint().GetX(), aaRectangle.GetTopLeftPoint().GetY()));
        }

        if(IsGreaterThanOrEqual(aaRectangle.GetBottomRightPoint().GetX(), mBoundary.GetBottomRightPoint().GetX())) {
            MoveTo(Vec2D(mBoundary.GetBottomRightPoint().GetX() - aaRectangle.GetWidth(), aaRectangle.GetTopLeftPoint().GetY()));
        }
    }
}

void Paddle::Draw(Screen &screen) {
    screen.Draw(GetAARectangle(), Color::Blue(), true, Color::Blue());
}

bool Paddle::Bounce(Ball &ball) {
    BoundaryEdge boundaryEdge;

    if(HasCollided(ball.GetBoundingRect(), boundaryEdge)) {
        Vec2D pointOnEdge;
        ball.MakeFlushWithEdge(boundaryEdge, pointOnEdge, true);

        if(boundaryEdge.edge == GetEdge(TOP_EDGE).edge) {
            float edgeLength = boundaryEdge.edge.Length();
            assert(!IsEqual(edgeLength, 0));

            float tx = (pointOnEdge.GetX() - boundaryEdge.edge.GetP0().GetX())/edgeLength;

            if((tx <= CORNER_BOUNCE_AMOUNT && ball.GetVelocity().GetX() > 0) || (tx >= (1.0f - CORNER_BOUNCE_AMOUNT) && ball.GetVelocity().GetX() < 0)) {
                ball.SetVelocity(-ball.GetVelocity());
                return true;
            }
        }

        ball.SetVelocity(ball.GetVelocity().Reflect(boundaryEdge.normal));
        return true;
    }

    return false;
}