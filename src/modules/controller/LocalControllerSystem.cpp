#include "LocalControllerSystem.h"
#include "core/SolWorld.h"

void LocalControllerSystem::preStep(SolWorld &world, double dt, double time)
{
    auto &inputs = world.inputs;
    auto &localUsers = world.localUsers;

    for (int i = 0; i < localUsers.size(); ++i)
    {
        int entityId = localUsers.getEntityAt(i);
        Comp::LocalUser *localUser = localUsers.get(entityId);
        Comp::Input *input = inputs.get(entityId);
        if (!input)
            continue;

        input->wishDirX = Input::wishdir();
        input->jumpRequested = Input::pressed(Actions::JUMP);
    }
}
