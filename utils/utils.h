//
// Created by ja on 6/4/24.
//

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

static const float EPSILON = 0.0001f;

const float PI = 3.14159f;
const float TWO_PI = PI * 2.0f;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MillisecondsToSeconds(unsigned milliseconds);

#endif /* UTILS_UTILS_H_ */