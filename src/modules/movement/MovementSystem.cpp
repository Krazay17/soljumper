#include "MovementSystem.h"
#include <iostream>
#include "core/SolWorld.h"
#include "graphics/Graphics.h"
#include "movement/MoveUtils.h"

void MovementSystem::step(SolWorld &world, double dt, double time)
{
    auto &velocities = world.velocities;
    auto &positions = world.positions;
    auto &inputs = world.inputs;

    for (int i = 0; i < velocities.size(); ++i)
    {
        int entityId = velocities.getEntityAt(i);
        InputComp *input = inputs.get(entityId);
        Velocity &vel = velocities.getByIndex(i);
        vel.vx = MoveUtils::accelerate(dt, vel.vx, vel.wishdir, vel.speed, vel.accel);
    }
}
