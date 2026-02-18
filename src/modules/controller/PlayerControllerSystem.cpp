#include "PlayerControllerSystem.h"
#include "core/SolWorld.h"

void PlayerControllerSystem::preStep(SolWorld &world, double dt, double time)
{
    auto &inputs = world.inputs;
    auto &users = world.users;

    for(int i =0; i < users.size(); ++i)
    {
        int entityId = world.users.getEntityAt(i);
        User *user = world.users.get(entityId);

        
    }
}
