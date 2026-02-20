#include "MovementSystem.h"
#include <iostream>
#include "core/SolWorld.h"
#include "graphics/Graphics.h"
#include "movement/MoveUtils.h"

void MovementSystem::step(SolWorld &world, double dt, double time)
{
    auto &velocities = world.velocities;
    auto &inputs = world.inputs;
    auto &bodies = world.bodies;

    for (int i = 0; i < inputs.size(); ++i)
    {
        int entityId = inputs.getEntityAt(i);
        Comp::Input &input = inputs.getByIndex(i);
        Comp::Velocity *vel = velocities.get(entityId);
        Comp::Body *body = bodies.get(entityId);
        if (!vel || !body)
            continue;
        const bool grounded = body->touching & BodyTouching::TOUCHING_DOWN;
        const float accel = grounded ? vel->groundAccel : vel->airAccel;
        vel->vx = MoveUtils::accelerate(dt, vel->vx, input.wishDirX, vel->speed, accel);

        if (input.jumpRequested && grounded)
        {
            vel->vy = -4.5;
        }
    }
}
