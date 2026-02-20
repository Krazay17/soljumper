#pragma once
#include "core/Ecs.h"
#include "core/SolWorld.h"
#include "graphics/Graphics.h"

class PointsSystem : public EcsSystem
{
public:
    PointsSystem() { flags = HAS_STEP | HAS_TICK; }
    inline void step(SolWorld &world, double dt, double time)
    {
        auto &gamePoints = world.singletonGamePoints;
        auto &points = world.gamePoints;
        auto &poss = world.positions;
        auto &bodies = world.bodies;
        if (points.size() < 1)
            gamePoints.win = true;
        for (int i = 0; i < points.size(); ++i)
        {
            int entityId = points.getEntityAt(i);
            auto &point = points.getByIndex(i);
            Comp::Position *pos = poss.get(entityId);
            if (pos->y > 780.0f)
            {
                gamePoints.score += 1;
                world.entitiesToRemove.push_back(entityId);
            }
        }
    }

    inline void tick(SolWorld &world, double dt, double time, double alpha)
    {
        auto &gamePoints = world.singletonGamePoints;
        std::string text = gamePoints.win ? "You Win!" : "Cubes pushed off: " + std::to_string(gamePoints.score);
        Gfx::drawText(text.c_str(), 600, 200);
    }
};