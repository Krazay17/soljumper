#pragma once
#include "SDL3/SDL.h"

enum Actions
{
    NONE = 0,
    CLICK = 1 << 0,
    LMOUSE = 1 << 1,
    RMOUSE = 1 << 2,
    FWD = 1 << 3,
    BWD = 1 << 4,
    LEFT = 1 << 5,
    RIGHT = 1 << 6,
    JUMP = 1 << 7,
};

namespace Input
{
    extern Uint32 hardwareState;
    extern Uint32 state;
    extern Uint32 lastState;
    extern Uint32 buffer;
    extern float mouseX;
    extern float mouseY;
    extern bool quitGame;

    inline bool held(Actions a)
    {
        return (state & a);
    }

    inline bool pressed(Actions a)
    {
        return (state & a) && !(lastState & a);
    }

    inline bool released(Actions a)
    {
        return !(state & a) && (lastState & a);
    }

    void handleEvent(const SDL_Event &e);
    void update();
    void preStep();
};
