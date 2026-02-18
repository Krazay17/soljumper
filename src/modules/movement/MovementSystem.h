#pragma once
#include "core/Ecs.h"

class MovementSystem : public EcsSystem
{
    void move(double dt);
    void applyGravity(float g);
    void applyCollision();
    void jump();
    float friction(double dt, float vel, float friction);
    float accelerate(double dt, float vel, int wishdir, float wishspeed, float accel);
    int wishdir();

public:
    MovementSystem() { flags = HAS_STEP; }
    void step(SolWorld &world, double dt, double time);
};