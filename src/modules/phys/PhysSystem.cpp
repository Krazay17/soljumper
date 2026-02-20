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
    float skin = 0;
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

    // 1. Movement pass — only dynamic bodies
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

        const float friction = (body->touching & BodyTouching::TOUCHING_DOWN)
                                   ? body->groundFriction
                                   : body->airFriction;
        vel->vx = MoveUtils::friction(dt, vel->vx, friction);
        body->touching = 0;
        vel->vy += 9.81f * dt;
        pos->x += vel->vx;
        pos->y += vel->vy;
    }

    // 2. Collision pass — all pairs
    for (int i = 0; i < bodies.size(); ++i)
    {
        int idA = bodies.getEntityAt(i);
        Comp::Body *bodyA = bodies.get(idA);
        Comp::Position *posA = positions.get(idA);
        if (!posA || !bodyA)
            continue;

        for (int j = i + 1; j < bodies.size(); ++j)
        {
            int idB = bodies.getEntityAt(j);
            Comp::Body *bodyB = bodies.get(idB);
            Comp::Position *posB = positions.get(idB);
            if (!posB || !bodyB)
                continue;

            // Skip if both static
            if (bodyA->type == BodyType::STATIC && bodyB->type == BodyType::STATIC)
                continue;

            float dx = posB->x - posA->x;
            float dy = posB->y - posA->y;
            float range = bodyA->width + bodyB->width;
            if ((dx * dx + dy * dy) > (range * range))
                continue;

            if (!AABB(posA->x, posA->x + bodyA->width, posA->y, posA->y + bodyA->height,
                      posB->x, posB->x + bodyB->width, posB->y, posB->y + bodyB->height))
                continue;

            Collision colX = getCollision(posA->x, bodyA->width, posB->x, bodyB->width);
            Collision colY = getCollision(posA->y, bodyA->height, posB->y, bodyB->height);

            bool resolveX = colX.overlap < colY.overlap;
            float overlap = resolveX ? colX.overlap : colY.overlap;
            float normal = resolveX ? colX.normal : colY.normal;

            // Resolve positions
            if (bodyA->type == BodyType::STATIC)
            {
                // Only push B
                if (resolveX)
                    posB->x -= overlap * normal;
                else
                    posB->y -= overlap * normal;
            }
            else if (bodyB->type == BodyType::STATIC)
            {
                // Only push A
                if (resolveX)
                    posA->x += overlap * normal;
                else
                    posA->y += overlap * normal;
            }
            else
            {
                // Both dynamic — split by mass
                float totalMass = bodyA->mass + bodyB->mass;
                float ratioA = bodyB->mass / totalMass;
                float ratioB = bodyA->mass / totalMass;
                if (resolveX)
                {
                    posA->x += overlap * normal * ratioA;
                    posB->x -= overlap * normal * ratioB;
                }
                else
                {
                    posA->y += overlap * normal * ratioA;
                    posB->y -= overlap * normal * ratioB;
                }
            }

            // Resolve velocities
            Comp::Velocity *velA = velocities.get(idA);
            Comp::Velocity *velB = velocities.get(idB);

            if (resolveX)
            {
                if (bodyA->type == BodyType::DYNAMIC)
                    bodyA->touching |= (normal < 0) ? TOUCHING_RIGHT : TOUCHING_LEFT;
                if (bodyB->type == BodyType::DYNAMIC)
                    bodyB->touching |= (normal < 0) ? TOUCHING_LEFT : TOUCHING_RIGHT;

                if (bodyA->type == BodyType::STATIC && velB)
                    velB->vx = 0;
                else if (bodyB->type == BodyType::STATIC && velA)
                    velA->vx = 0;
                else if (velA && velB && relativeVel(velA->vx, velB->vx, posA->x, posB->x))
                {
                    float totalMass = bodyA->mass + bodyB->mass;
                    float combined = (velA->vx * bodyA->mass + velB->vx * bodyB->mass) / totalMass;
                    velA->vx = combined;
                    velB->vx = combined;
                }
            }
            else
            {
                if (bodyA->type == BodyType::DYNAMIC)
                    bodyA->touching |= (normal < 0) ? TOUCHING_DOWN : TOUCHING_UP;
                if (bodyB->type == BodyType::DYNAMIC)
                    bodyB->touching |= (normal < 0) ? TOUCHING_UP : TOUCHING_DOWN;

                if (bodyA->type == BodyType::STATIC && velB)
                    velB->vy = 0;
                else if (bodyB->type == BodyType::STATIC && velA)
                    velA->vy = 0;
                else if (velA && velB && relativeVel(velA->vy, velB->vy, posA->y, posB->y))
                {
                    float totalMass = bodyA->mass + bodyB->mass;
                    float combined = (velA->vy * bodyA->mass + velB->vy * bodyB->mass) / totalMass;
                    velA->vy = combined;
                    velB->vy = combined;
                }
            }
        }
    }
}