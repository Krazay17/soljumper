#pragma once
#include "math/Vec2.h"
#include <SDL3/SDL.h>

enum ComponentBit
{
    POSITION = 1 << 0,
    VELOCITY = 1 << 1,
};

struct Position
{
    float x, y;
};

struct Velocity
{
    float vx, vy;
};