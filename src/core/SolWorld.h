#pragma once
#include <vector>
#include "Ecs.h"
#include "Components.h"
#include <bitset>
#include <unordered_map>

//using Signature = std::bitset<32>;
struct Entity
{
    int id;
    int signature;
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

    std::vector<Position> positions;
    std::vector<Velocity> velocities;

public:
    SolWorld();
    void preStep(double dt, double time);
    void step(double dt, double time);
    void postStep(double dt, double time);
    void tick(double dt, double time, double alpha);
    int createEntity();
    void addComponent(int entityId, ComponentBit bit);
    std::vector<Entity> &getEntities();
    void destroyEntity(int id);

};