#pragma once
#include <cmath>
#include "input/Input.h"
#include "math/Vec2.h"

namespace MoveUtils
{
    inline float friction(double dt, float vel, float friction)
    {
        const float speed = std::abs(vel);
        if (speed < 0.01f)
            return 0.0f;
        const float drop = speed * friction * dt;
        const float newSpeed = std::max(0.0f, speed - drop);
        return vel * (newSpeed / speed);
    }

    inline float accelerate(double dt, float vel, int wishdir, float wishspeed, float accel)
    {
        const float dirSpeed = vel * wishdir;
        const float addSpeed = wishspeed - dirSpeed;
        if (addSpeed <= 0)
            return vel;
        const float accelSpeed = accel * wishspeed * dt;
        const float final = std::min(accelSpeed, addSpeed);
        return vel + (wishdir * final);
    }

}