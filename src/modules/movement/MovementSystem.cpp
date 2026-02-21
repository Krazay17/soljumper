#include "MovementSystem.h"
#include <iostream>
#include "core/SolWorld.h"
#include "graphics/Graphics.h"
#include "movement/MoveUtils.h"

void MovementSystem::step(SolWorld &world, double dt, double time)
{
    auto &inputs = world.inputs;
    auto &physics = world.physics;

    for (int i = 0; i < inputs.size(); ++i)
    {
        int entityId = inputs.getEntityAt(i);
        Comp::Input &input = inputs.getByIndex(i);
        Comp::Physics *phys = physics.get(entityId);
        if (!phys)
            continue;
        const bool grounded = phys->touching & BodyTouching::TOUCHING_DOWN;
        const float accel = grounded ? phys->gAccel: phys->aAccel;
        phys->vx = MoveUtils::accelerate(dt, phys->vx, input.wishDirX, phys->gSpeed, accel);

        if (input.jumpRequested && grounded)
        {
            phys->vy = -4.5;
        }
    }
}
