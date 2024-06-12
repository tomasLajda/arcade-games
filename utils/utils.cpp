//
// Created by ja on 6/4/24.
//

#include "utils.h"
#include <cmath>

bool IsEqual(float x, float y){
    return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y){
    return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y){
    return x < y || IsEqual(x, y);
}
