#pragma once
#include "core/Ecs.h"
#include "SolWorld.h"

namespace Factory
{
    inline int makeEnemy(SolWorld &world, float x, float y, float h = 15.0f, float w = 15.0f, float m = 5.0f)
    {
        const int id = world.createEntity();
        auto &pos = world.positions.add(id);
        pos.x = x;
        pos.y = y;
        world.velocities.add(id);
        auto &sprite = world.sprites.add(id);
        sprite.width = w;
        sprite.height = h;
        auto &body = world.bodies.add(id);
        body.width = w;
        body.height = h;
        body.type = BodyType::DYNAMIC;
        body.mass = m;

        return id;
    }
    inline int makeFloor(SolWorld &world, float x, float y, float h = 15.0f, float w = 50.0f)
    {
        const int id = world.createEntity();
        auto &pos = world.positions.add(id);
        pos.x = x;
        pos.y = y;
        auto &sprite = world.sprites.add(id);
        sprite.width = w;
        sprite.height = h;
        sprite.color = {0, 255, 0, 255};
        auto &body = world.bodies.add(id);
        body.width = w;
        body.height = h;
        body.type = BodyType::STATIC;

        return id;
    }
};