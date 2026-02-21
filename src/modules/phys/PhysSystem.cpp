#include "PhysSystem.h"
#include <iostream>
#include "movement/MoveUtils.h"
#include "core/SolWorld.h"

Collision getCollision(float aPos, float aWidth, float bPos, float bWidth)
{
    Collision col;
    float centerA = aPos + (aWidth / 2.0f);
    float centerB = bPos + (bWidth / 2.0f);
    col.normal = (centerA < centerB) ? -1.0f : 1.0f;
    float depth = std::abs(centerA - centerB);
    float combinedDepth = aWidth / 2.0f + bWidth / 2.0f;
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
    return L1 < R2 && R1 > L2 && T1 < B2 && B1 > T2;
}

bool relativeVel(float vel1, float vel2, float pos1, float pos2)
{
    float vel = vel1 - vel2;
    return (pos1 < pos2 && vel > 0.001f) || (pos1 > pos2 && vel < -0.001f);
}

void PhysSystem::step(SolWorld &world, double dt, double time)
{
    auto &physics = world.physics;
    const int count = static_cast<int>(physics.size());

    // 1. Integration Pass
    for (int i = 0; i < count; ++i)
    {
        auto &aPhys = physics.getByIndex(i);
        if (!aPhys.isDynamic())
            continue;

        const float friction = (aPhys.touching & BodyTouching::TOUCHING_DOWN)
                                   ? aPhys.gFriction
                                   : aPhys.aFriction;

        aPhys.vx = MoveUtils::friction(dt, aPhys.vx, friction);
        aPhys.vy += 9.81f * dt;

        aPhys.touching = 0; // Reset flags for resolution pass
        aPhys.x += aPhys.vx;
        aPhys.y += aPhys.vy;
    }

    // 2. Collision & Resolution Pass
    for (int i = 0; i < count; ++i)
    {
        auto &aPhys = physics.getByIndex(i);

        for (int j = i + 1; j < count; ++j)
        {
            auto &bPhys = physics.getByIndex(j);

            // Skip if both static
            if (!aPhys.isDynamic() && !bPhys.isDynamic())
                continue;

            if (AABB(aPhys.x, aPhys.x + aPhys.w, aPhys.y, aPhys.y + aPhys.h,
                     bPhys.x, bPhys.x + bPhys.w, bPhys.y, bPhys.y + bPhys.h))
            {
                Collision colX = getCollision(aPhys.x, aPhys.w, bPhys.x, bPhys.w);
                Collision colY = getCollision(aPhys.y, aPhys.h, bPhys.y, bPhys.h);

                // Axis of least penetration
                bool resolveX = colX.overlap < colY.overlap;
                float overlap = resolveX ? colX.overlap : colY.overlap;
                float normal = resolveX ? colX.normal : colY.normal;

                // --- Position Resolution ---
                float totalMass = aPhys.mass + bPhys.mass;
                float ratioA = bPhys.isDynamic() ? (aPhys.isDynamic() ? bPhys.mass / totalMass : 0.0f) : 1.0f;
                float ratioB = aPhys.isDynamic() ? (bPhys.isDynamic() ? aPhys.mass / totalMass : 0.0f) : 1.0f;

                // Static overrides: if A is static, ratioB is 1. If B is static, ratioA is 1.
                if (!aPhys.isDynamic())
                {
                    ratioA = 0.0f;
                    ratioB = 1.0f;
                }
                else if (!bPhys.isDynamic())
                {
                    ratioA = 1.0f;
                    ratioB = 0.0f;
                }

                if (resolveX)
                {
                    aPhys.x += overlap * normal * ratioA;
                    bPhys.x -= overlap * normal * ratioB;
                }
                else
                {
                    aPhys.y += overlap * normal * ratioA;
                    bPhys.y -= overlap * normal * ratioB;
                }

                // --- Velocity & Touching Resolution via relativeVel ---
                if (resolveX)
                {
                    // Update touching flags
                    if (aPhys.isDynamic())
                        aPhys.touching |= (normal < 0) ? BodyTouching::TOUCHING_RIGHT : BodyTouching::TOUCHING_LEFT;
                    if (bPhys.isDynamic())
                        bPhys.touching |= (normal < 0) ? BodyTouching::TOUCHING_LEFT : BodyTouching::TOUCHING_RIGHT;

                    // Resolve Velocity
                    if (relativeVel(aPhys.vx, bPhys.vx, aPhys.x, bPhys.x))
                    {
                        if (!aPhys.isDynamic())
                            bPhys.vx = 0;
                        else if (!bPhys.isDynamic())
                            aPhys.vx = 0;
                        else
                        {
                            float vA = contactPush(aPhys.vx, bPhys.vx, aPhys.mass, bPhys.mass);
                            float vB = contactPush(bPhys.vx, aPhys.vx, bPhys.mass, aPhys.mass);
                            aPhys.vx = vA;
                            bPhys.vx = vB;
                        }
                    }
                }
                else
                {
                    // Update touching flags
                    if (aPhys.isDynamic())
                        aPhys.touching |= (normal < 0) ? BodyTouching::TOUCHING_DOWN : BodyTouching::TOUCHING_UP;
                    if (bPhys.isDynamic())
                        bPhys.touching |= (normal < 0) ? BodyTouching::TOUCHING_UP : BodyTouching::TOUCHING_DOWN;

                    // Resolve Velocity
                    if (relativeVel(aPhys.vy, bPhys.vy, aPhys.y, bPhys.y))
                    {
                        if (!aPhys.isDynamic())
                            bPhys.vy = 0;
                        else if (!bPhys.isDynamic())
                            aPhys.vy = 0;
                        else
                        {
                            float vA = contactPush(aPhys.vy, bPhys.vy, aPhys.mass, bPhys.mass);
                            float vB = contactPush(bPhys.vy, aPhys.vy, bPhys.mass, aPhys.mass);
                            aPhys.vy = vA;
                            bPhys.vy = vB;
                        }
                    }
                }
            }
        }
    }
}