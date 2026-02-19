#pragma once
#include "core/Ecs.h"
#include "core/SolWorld.h"
#include "graphics/Graphics.h"
#include "ui/Button.h"
#include <vector>

class InventorySystem : public EcsSystem
{
    std::vector<Button> Buttons;

public:
    InventorySystem() { flags = HAS_TICK; }
    inline void step(SolWorld &world, double dt, double time)
    {
        auto &inventories = world.inventories;

        for (int i = 0; i < inventories.size(); ++i)
        {
            int entityId = inventories.getEntityAt(i);
            Comp::Inventory &inventory = inventories.getByIndex(i);
            
        }
    }
    inline void tick(SolWorld &world, double dt, double time, double alpha)
    {
        auto &inputs = world.inputs;

        for (int i = 0; i < inputs.size(); ++i)
        {
            int entityId = inputs.getEntityAt(i);
            Comp::Input &input = inputs.getByIndex(i);

            if (input.inventory)
            {
                Gfx::drawRect(800, 0, 200, 700, {122, 122, 0, 255});
            }
        }
    }
};