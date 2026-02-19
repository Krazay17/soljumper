#pragma once
#include "core/Ecs.h"

struct Collision
{
    float normal = 0;
    float depth = 0;
    float overlap = 0;
};
class PhysSystem : public EcsSystem
{
public:
    PhysSystem()
    {
        flags = HAS_STEP;
        required = ComponentBit::POSITION | ComponentBit::VELOCITY;
    }
    void step(SolWorld &world, double dt, double time);
};