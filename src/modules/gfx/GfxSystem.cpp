#include "GfxSystem.h"
#include "core/SolWorld.h"
#include "graphics/Graphics.h"

void GfxSystem::tick(SolWorld &world, double dt, double time, double alpha)
{
    auto &position = world.positions;
    auto &sprites = world.sprites;
    
    for (int i = 0; i < sprites.size(); ++i)
    {
        int entityId = sprites.getEntityAt(i);
        Comp::Sprite *sprite = sprites.get(entityId);
        Comp::Position *pos = position.get(entityId);

        Gfx::drawRect(pos->x, pos->y, sprite->width, sprite->height, sprite->color);
    }
}