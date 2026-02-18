#pragma once
#include "core/Ecs.h"
#include "input/Input.h"

class PlayerControllerSystem:public EcsSystem
{
    PlayerControllerSystem(){flags = HAS_PRESTEP;}
    void preStep(SolWorld &world, double dt, double time);
};