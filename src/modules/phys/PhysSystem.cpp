#include "PhysSystem.h"
#include <iostream>
#include "movement/MoveUtils.h"
#include "core/SolWorld.h"

void PhysSystem::preStep(SolWorld &world, double dt, double time)
{
}

void PhysSystem::step(SolWorld &world, double dt, double time)
{
    auto &bodies = world.bodies;
    auto &positions = world.positions;
    auto &velocities = world.velocities;
    for (int i = 0; i < bodies.size(); ++i)
    {
        int entityId = bodies.getEntityAt(i);
        Body *body = bodies.get(entityId);
        if (body->type == BodyType::STATIC)
            continue;

        Velocity *vel = velocities.get(entityId);
        Position *pos = positions.get(entityId);
        if (!pos || !vel)
            continue;

        const float friction = (body->touching & BodyTouching::TOUCHING_DOWN) ? body->groundFriction : body->airFriction;
        vel->vx = MoveUtils::friction(dt, vel->vx, friction);

        body->touching = 0;

        // --- 1. HORIZONTAL AXIS ---
        // Apply X movement
        pos->x += vel->vx;

        for (int j = 0; j < bodies.size(); ++j)
        {
            int otherId = bodies.getEntityAt(j);
            if (entityId == otherId)
                continue;
            Body *otherBody = bodies.get(otherId);
            Position *otherPos = positions.get(otherId);

            // AABB Check on X
            if (pos->x < otherPos->x + otherBody->width && pos->x + body->width > otherPos->x &&
                pos->y < otherPos->y + otherBody->height && pos->y + body->height > otherPos->y)
            {
                // Moving Right
                if (vel->vx > 0)
                { 
                    pos->x = otherPos->x - body->width;
                    body->touching |= BodyTouching::TOUCHING_RIGHT;
                }
                // Moving Left
                else if (vel->vx < 0)
                { 
                    pos->x = otherPos->x + otherBody->width;
                    body->touching |= BodyTouching::TOUCHING_LEFT;
                }
                vel->vx = 0;
            }
        }

        // --- 2. VERTICAL AXIS ---
        vel->vy += 9.81f * dt;
        // Apply Y movement
        pos->y += vel->vy;

        for (int j = 0; j < bodies.size(); ++j)
        {
            int otherId = bodies.getEntityAt(j);
            if (entityId == otherId)
                continue;
            Body *otherBody = bodies.get(otherId);
            Position *otherPos = positions.get(otherId);

            // AABB Check on Y
            if (pos->x < otherPos->x + otherBody->width && pos->x + body->width > otherPos->x &&
                pos->y < otherPos->y + otherBody->height && pos->y + body->height > otherPos->y)
            {
                // Move Down
                if (vel->vy > 0)
                {
                    pos->y = otherPos->y - body->height;
                    body->touching |= BodyTouching::TOUCHING_DOWN;
                }
                // Move Up
                else if (vel->vy < 0)
                {
                    pos->y = otherPos->y + otherBody->height;
                    body->touching |= BodyTouching::TOUCHING_UP;
                }
                vel->vy = 0;
            }
        }
    }
}

void PhysSystem::postStep(SolWorld &world, double dt, double time)
{
}