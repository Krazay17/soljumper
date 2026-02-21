#include "GfxSystem.h"
#include "core/SolWorld.h"
#include "graphics/Graphics.h"

void GfxSystem::tick(SolWorld &world, double dt, double time, double alpha)
{
    auto &sprites = world.sprites;
    auto &physics = world.physics;
    //auto &position = world.positions;
    
    for (int i = 0; i < sprites.size(); ++i)
    {
        int entityId = sprites.getEntityAt(i);
        Comp::Sprite *sprite = sprites.get(entityId);
        //Comp::Position *pos = position.get(entityId);
        Comp::Physics *phys = physics.get(entityId);

        //Gfx::drawRect(pos->x, pos->y, sprite->width, sprite->height, sprite->color);
        Gfx::drawRect(phys->x, phys->y, sprite->width, sprite->height, sprite->color);
    }
}