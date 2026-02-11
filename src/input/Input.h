#pragma once
#include "SDL3/SDL.h"

enum Actions
{
    NONE = 0,
    CLICK = 1 << 0,
    FWD = 1 << 1,
    JUMP = 1 << 2,
};

namespace Input
{
    extern Uint32 actionMask;
    extern Uint32 lastActionMask;
    extern float mouseX;
    extern float mouseY;
    inline bool pressed(Actions a) { 
        return (actionMask & a) && !(lastActionMask & a); 
    }

    void update(SDL_Event event);
    void postUpdate();
};
