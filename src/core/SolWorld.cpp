#include "SolWorld.h"
#include "modules/controller/LocalControllerSystem.h"
#include "modules/phys/PhysSystem.h"
#include "modules/gfx/GfxSystem.h"
#include "modules/movement/MovementSystem.h"
#include "modules/inventory/InventorySystem.h"
#include "modules/points/PointsSystem.h"

SolWorld::SolWorld()
{
    Systems.push_back(new LocalControllerSystem());
    Systems.push_back(new MovementSystem());
    Systems.push_back(new PhysSystem());
    Systems.push_back(new GfxSystem());
    Systems.push_back(new InventorySystem());
    Systems.push_back(new PointsSystem());

    allComponents.insert(allComponents.end(), {&positions,
                                               &bodies,
                                               &velocities,
                                               &sprites,
                                               &inputs,
                                               &localUsers,
                                               &users,
                                               &inventories,
                                               &gamePoints,
                                               &physics});


    for (auto *s : Systems)
    {
        if (s->flags & HAS_PRESTEP)
            preSystems.push_back(s);
        if (s->flags & HAS_STEP)
            stepSystems.push_back(s);
        if (s->flags & HAS_POSTSTEP)
            postSystems.push_back(s);
        if (s->flags & HAS_TICK)
            tickSystems.push_back(s);
    }
}

void SolWorld::preStep(double dt, double time)
{
    for (auto *s : preSystems)
        s->preStep(*this, dt, time);
}

void SolWorld::step(double dt, double time)
{

    for (auto *s : stepSystems)
        s->step(*this, dt, time);
}

void SolWorld::postStep(double dt, double time)
{

    for (auto *s : postSystems)
        s->postStep(*this, dt, time);

    if (entitiesToRemove.empty())
        return;

    for (int id : entitiesToRemove)
    {
        for (auto &comp : allComponents)
        {
            comp->remove(id, true);
        }
    }
    entitiesToRemove.clear();
}

void SolWorld::tick(double dt, double time, double alpha)
{
    for (auto *s : tickSystems)
        s->tick(*this, dt, time, alpha);
}

int SolWorld::createEntity()
{
    int id = nextId++;
    entities.push_back({id, 0});

    return id;
}

std::vector<Entity> &SolWorld::getEntities()
{
    return entities;
}