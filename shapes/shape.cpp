//
// Created by ja on 6/21/24.
//

#include "shape.h"

void Shape::MoveBy(const Vec2D &deltaOffset) {
    for(Vec2D &point : mPoints) {
        point += deltaOffset;
    }
}
