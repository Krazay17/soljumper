#include "SolWorld.h"
#include "modules/phys/PhysSystem.h"
#include "modules/gfx/GfxSystem.h"
#include "modules/movement/MovementSystem.h"


SolWorld::SolWorld()
{
    Systems.push_back(new MovementSystem());
    Systems.push_back(new PhysSystem());
    Systems.push_back(new GfxSystem());

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
}

void SolWorld::tick(double dt, double time, double alpha)
{

    for (auto *s : tickSystems)
        s->tick(*this, dt, time, alpha);
}

int SolWorld::createEntity()
{
    int id = nextId++;

    if (id >= eIdToIndex.size())
    {
        eIdToIndex.resize(id + 1, -1);
    }

    eIdToIndex[id] = entities.size();
    entities.push_back({id, 0});

    return id;
}

std::vector<Entity> &SolWorld::getEntities()
{
    return entities;
}