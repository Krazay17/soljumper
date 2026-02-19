#pragma once
#include "core/Ecs.h"
#include "SolWorld.h"

namespace Factory
{
    inline int makeEnemy(SolWorld &world, float x, float y)
    {
        const int id = world.createEntity();
        auto &pos = world.positions.add(id);
        pos.x = x;
        pos.y = y;
        world.velocities.add(id);
        auto &sprite = world.sprites.add(id);
        sprite.width = 15.0f;
        sprite.height = 15.0f;
        auto &body = world.bodies.add(id);
        body.width = 15.0f;
        body.height = 15.0f;
        body.type = BodyType::DYNAMIC;
        body.mass = 5.0f;

        return id;
    }
};