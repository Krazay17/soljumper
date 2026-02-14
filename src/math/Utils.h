#pragma once
#include <cmath>

inline float lerp(float a, float b, float speed, float dt = 0.016f)
{
    float alpha = 1.0f - std::exp(-speed * dt);
    return a + (b - a) * alpha;
}

inline float lerp_linear(float a, float b, float t)
{
    return a + t * (b - a);
}