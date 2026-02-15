#include "PhysSystem.h"
#include "core/SolWorld.h"

void PhysSystem::preStep(SolWorld &world, double dt, double time)
{
}

void PhysSystem::step(SolWorld &world, double dt, double time)
{
    for (auto &entity : world.getEntities())
    {
        if ((entity.signature & required) == required)
        {
            
        }
    }
}

void PhysSystem::postStep(SolWorld &world, double dt, double time)
{
}