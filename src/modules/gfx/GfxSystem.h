#pragma once
#include "core/Ecs.h"

class GfxSystem : public EcsSystem
{
    public:
    GfxSystem() { flags = HAS_TICK; }
    void tick(SolWorld &world, double dt, double time, double alpha);
};