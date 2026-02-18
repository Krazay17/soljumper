#pragma once
#include "core/Ecs.h"
#include "input/Input.h"

class LocalControllerSystem : public EcsSystem
{
public:
    LocalControllerSystem() { flags = HAS_PRESTEP; }
    void preStep(SolWorld &world, double dt, double time);
};