#pragma once
#include "core/Ecs.h"
#include "SolWorld.h"

namespace Factory
{
    inline int makeEnemy(SolWorld &world, float x, float y, float h = 15.0f, float w = 15.0f, float m = 5.0f)
    {
        const int id = world.createEntity();

        auto &phys = world.physics.add(id);
        phys.x = x;
        phys.y = y;
        phys.w = w;
        phys.h = h;
        phys.mass = 1.0f;
        phys.type = BodyType::DYNAMIC;
        auto &sprite = world.sprites.add(id);
        sprite.width = w;
        sprite.height = h;
        sprite.color = {255, 0, 0, 255};
        return id;
    }

    inline int makeFloor(SolWorld &world, float x, float y, float w = 50.0f, float h = 15.0f)
    {
        const int id = world.createEntity();

        auto &phys = world.physics.add(id);
        phys.x = x;
        phys.y = y;
        phys.w = w;
        phys.h = h;
        phys.type = BodyType::STATIC;
        auto &sprite = world.sprites.add(id);
        sprite.width = w;
        sprite.height = h;
        sprite.color = {0, 255, 0, 255};
        return id;
    }
};