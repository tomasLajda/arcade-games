//
// Created by ja on 7/3/24.
//

#ifndef ARCADE_GAMES_PADDLE_H
#define ARCADE_GAMES_PADDLE_H

#include "excluder.h"
#include <cstdlib>

class Screen;
class Ball;

enum PaddleDirection {
    LEFT = 0b1,
    RIGHT = 0b10
};

class Paddle: public Excluder {
public:
    void Init(const AARectangle &rect, const AARectangle &boundary);
    void Update(u_int32_t deltaTime, Ball &ball);
    void Draw(Screen &screen);
    bool Bounce(Ball &ball);

    inline bool IsMovingLeft() const {return mDirection == PaddleDirection::LEFT;}
    inline bool IsMovingRight() const {return mDirection == PaddleDirection::RIGHT;}

    inline void SetMovementDirection(PaddleDirection dir) {mDirection |= dir;}
    inline void UnsetMovementDirection(PaddleDirection dir) {mDirection &= ~dir;}
    inline void StopMovement() {mDirection = 0;}

public:
    static const u_int32_t PADDLE_WIDTH = 50;
    static const u_int32_t PADDLE_HEIGHT = 10;

private:
    u_int32_t mDirection;
    AARectangle mBoundary;
    const float VELOCITY = 100.0f; // per second
    const float CORNER_BOUNCE_AMOUNT = 0.2f;
};


#endif//ARCADE_GAMES_PADDLE_H
