#pragma once
#include "core/Ecs.h"

class PhysSystem : public EcsSystem
{
public:
    PhysSystem()
    {
        flags = HAS_PRESTEP | HAS_STEP | HAS_POSTSTEP;
        required = ComponentBit::POSITION | ComponentBit::VELOCITY;
    }
    void preStep(SolWorld &world, double dt, double time);
    void step(SolWorld &world, double dt, double time);
    void postStep(SolWorld &world, double dt, double time);
};