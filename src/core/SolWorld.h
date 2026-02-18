#pragma once
#include <vector>
#include "Ecs.h"
#include "Components.h"
#include <bitset>
#include <unordered_map>

// using Signature = std::bitset<32>;
struct Entity
{
    int id;
    int signature;
};

template <typename T>
class ComponentPool
{
private:
    // The actual data, packed tight: [Pos1, Pos2, Pos3]
    std::vector<T> denseData;

    // Maps Dense Index -> Entity ID: [ID:5, ID:2, ID:10]
    std::vector<int> denseToEntity;

    // Maps Entity ID -> Dense Index: [ID 0: -1, ID 1: -1, ID 2: 1, ...]
    // This is the "Sparse" array. It can be large and full of holes.
    std::vector<int> entityToDense;

public:
    // 1. Add a component to an entity
    T &add(int entityId)
    {
        if (entityId >= entityToDense.size())
        {
            entityToDense.resize(entityId + 1, -1);
        }

        // Point Entity ID to the next available slot in denseData
        entityToDense[entityId] = static_cast<int>(denseData.size());
        denseToEntity.push_back(entityId);
        denseData.emplace_back(); // Create the actual component

        return denseData.back();
    }

    // 2. Get a component by Entity ID
    T *get(int entityId)
    {
        if (entityId < entityToDense.size() && entityToDense[entityId] != -1)
        {
            return &denseData[entityToDense[entityId]];
        }
        return nullptr;
    }

    // 3. The "Swap & Pop" (The magic of Sparse Sets)
    void remove(int entityId)
    {
        if (entityId >= entityToDense.size() || entityToDense[entityId] == -1)
            return;

        int indexToRemove = entityToDense[entityId];
        int lastIndex = static_cast<int>(denseData.size()) - 1;

        if (indexToRemove != lastIndex)
        {
            // Swap current with the last one to keep denseData packed
            T lastComponent = denseData[lastIndex];
            int lastEntityId = denseToEntity[lastIndex];

            denseData[indexToRemove] = lastComponent;
            denseToEntity[indexToRemove] = lastEntityId;

            // Update the sparse map for the entity that was moved!
            entityToDense[lastEntityId] = indexToRemove;
        }

        denseData.pop_back();
        denseToEntity.pop_back();
        entityToDense[entityId] = -1;
    }

    // Helpers for Systems to iterate fast
    size_t size() const { return denseData.size(); }
    T &getByIndex(int index) { return denseData[index]; }
    int getEntityAt(int index) { return denseToEntity[index]; }
};

class SolWorld
{
    int nextId = 0;
    std::vector<Entity> entities;
    std::vector<int> eIdToIndex;
    std::vector<EcsSystem *> Systems;
    std::vector<EcsSystem *> preSystems;
    std::vector<EcsSystem *> stepSystems;
    std::vector<EcsSystem *> postSystems;
    std::vector<EcsSystem *> tickSystems;

public:
    SolWorld();
    
    ComponentPool<Position> positions;
    ComponentPool<Body> bodies;
    ComponentPool<Velocity> velocities;
    ComponentPool<Sprite> sprites;
    ComponentPool<InputComp> inputs;
    ComponentPool<User> users;

    int localUserId;

    void preStep(double dt, double time);
    void step(double dt, double time);
    void postStep(double dt, double time);
    void tick(double dt, double time, double alpha);
    int createEntity();
    std::vector<Entity> &getEntities();
};