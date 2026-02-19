#include "PhysSystem.h"
#include <iostream>
#include "movement/MoveUtils.h"
#include "core/SolWorld.h"

Collision getCollision(float aPos, float aWidth, float bPos, float bWidth)
{
    Collision col;

    float centerA = aPos + (aWidth / 2.0f);
    float centerB = bPos + (bWidth / 2.0f);
    float normal = (centerA < centerB) ? -1.0f : 1.0f;
    float depth = std::abs(centerA - centerB);
    float combinedDepth = aWidth / 2.0f + bWidth / 2.0f;
    col.normal = normal;
    col.depth = depth;
    col.overlap = combinedDepth - depth;
    return col;
}

float contactPush(float v1, float v2, float m1, float m2)
{
    return (v1 * (m1 - m2) + (2.0f * m2 * v2)) / (m1 + m2);
}

bool AABB(float L1, float R1, float T1, float B1, float L2, float R2, float T2, float B2)
{
    float skin = 0.1f;
    return L1 < R2 - skin &&
           R1 > L2 + skin &&
           T1 < B2 - skin &&
           B1 > T2 + skin;
}

bool relativeVel(float vel1, float vel2, float pos1, float pos2)
{
    float vel = vel1 - vel2;
    return (pos1 < pos2 && vel > 0.001f) || (pos1 > pos2 && vel < 0.001f);
}

void PhysSystem::step(SolWorld &world, double dt, double time)
{
    auto &bodies = world.bodies;
    auto &positions = world.positions;
    auto &velocities = world.velocities;
    for (int i = 0; i < bodies.size(); ++i)
    {
        int entityId = bodies.getEntityAt(i);
        Comp::Body *body = bodies.get(entityId);
        if (body->type == BodyType::STATIC)
            continue;

        Comp::Velocity *vel = velocities.get(entityId);
        Comp::Position *pos = positions.get(entityId);
        if (!pos || !vel)
            continue;

        const float friction = (body->touching & BodyTouching::TOUCHING_DOWN) ? body->groundFriction : body->airFriction;
        vel->vx = MoveUtils::friction(dt, vel->vx, friction);

        body->touching = 0;
        vel->vy += 9.81f * dt;
        pos->x += vel->vx;
        pos->y += vel->vy;

        for (int j = i + 1; j < bodies.size(); ++j)
        {
            int otherId = bodies.getEntityAt(j);
            if (entityId == otherId)
                continue;
            Comp::Body *otherBody = bodies.get(otherId);
            Comp::Position *otherPos = positions.get(otherId);
            Comp::Velocity *otherVel = velocities.get(otherId);
            float dx = otherPos->x - pos->x;
            float dy = otherPos->y - pos->y;
            float range = (body->width + otherBody->width);
            // Fast squared distance check (no sqrt)
            if ((dx * dx + dy * dy) > (range * range))
                continue;

            if (AABB(pos->x, pos->x + body->width, pos->y, pos->y + body->height,
                     otherPos->x, otherPos->x + otherBody->width, otherPos->y, otherPos->y + otherBody->height))
            {
                Collision collisionX = getCollision(pos->x, body->width, otherPos->x, otherBody->width);
                Collision collisionY = getCollision(pos->y, body->height, otherPos->y, otherBody->height);

                float totalMass = body->mass + otherBody->mass;
                float pushRatio = otherBody->mass / totalMass;
                if (collisionX.overlap < collisionY.overlap)
                {
                    if (collisionX.normal < 0)
                        body->touching |= BodyTouching::TOUCHING_RIGHT;
                    if (collisionX.normal > 0)
                        body->touching |= BodyTouching::TOUCHING_LEFT;

                    float totalMass = body->mass + otherBody->mass;
                    float pushRatio = otherBody->mass / totalMass;

                    pos->x += collisionX.overlap * collisionX.normal * pushRatio;

                    if (otherBody->type == BodyType::STATIC)
                    {
                        vel->vx = 0;
                    }
                    else if (relativeVel(vel->vx, otherVel->vx, pos->x, otherPos->x))
                    {
                        float totalMass = body->mass + otherBody->mass;
                        float combinedVel = (vel->vx * body->mass + otherVel->vx * otherBody->mass) / totalMass;

                        vel->vx = combinedVel;
                        otherVel->vx = combinedVel;
                    }
                }
                else
                {
                    if (collisionY.normal < 0)
                    {
                        body->touching |= BodyTouching::TOUCHING_DOWN;
                    }
                    if (collisionY.normal > 0)
                        body->touching |= BodyTouching::TOUCHING_UP;

                    pos->y += collisionY.overlap * collisionY.normal * pushRatio;

                    if (otherBody->type == BodyType::STATIC)
                    {
                        vel->vy = 0;
                    }
                    else if (relativeVel(vel->vy, otherVel->vy, pos->y, otherPos->y))
                    {
                        float totalMass = body->mass + otherBody->mass;
                        float combinedVel = (vel->vy * body->mass + otherVel->vy * otherBody->mass) / totalMass;

                        vel->vy = combinedVel;
                        otherVel->vy = combinedVel;
                    }
                }
            }
        }
    }
}