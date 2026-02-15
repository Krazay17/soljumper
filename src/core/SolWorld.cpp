#include "SolWorld.h"
#include "modules/phys/PhysSystem.h"

SolWorld::SolWorld()
{
    Systems.push_back(new PhysSystem());

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

    positions.emplace_back();
    velocities.emplace_back();

    return id;
}

void SolWorld::addComponent(int entityId, ComponentBit bit)
{
    int index = eIdToIndex[entityId];
    if(index != -1 && index < entities.size())
    {
        entities[index].signature |= bit;
    }
}

std::vector<Entity> &SolWorld::getEntities()
{
    return entities;
}

void SolWorld::destroyEntity(int id) {
    int indexToRemove = eIdToIndex[id];
    int lastIndex = entities.size() - 1;

    // 1. If we aren't already the last item, swap with the last item
    if (indexToRemove != lastIndex) {
        // Get the ID of the entity that is currently at the very end
        int lastEntityId = entities[lastIndex].id;

        // Move the last entity's data into the slot of the one we are deleting
        entities[indexToRemove] = entities[lastIndex];
        positions[indexToRemove] = positions[lastIndex];
        velocities[indexToRemove] = velocities[lastIndex];

        // IMPORTANT: Update the lookup table for the entity that moved!
        // "Hey ID #X, you aren't at the end anymore, you're now at indexToRemove"
        eIdToIndex[lastEntityId] = indexToRemove;
    }

    // 2. Now the "dead" data is at the end of the vectors. Pop it!
    entities.pop_back();
    positions.pop_back();
    velocities.pop_back();

    // 3. Mark the destroyed ID as invalid in our lookup table
    eIdToIndex[id] = -1;
}