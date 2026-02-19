#include "Input.h"
#include <iostream>

namespace Input
{
    Uint32 hardwareState;
    Uint32 state;
    Uint32 lastState;
    Uint32 buffer;
    float mouseX = 0;
    float mouseY = 0;
    bool quitGame = false;

    void handleEvent(const SDL_Event &e)
    {
        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            buffer |= CLICK;
        }
        if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == 99)
        {
            buffer |= INVENTORY;
        }
    }

    void update()
    {
        const Uint32 mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseButtons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT))
            hardwareState |= CLICK;
        else
            hardwareState &= ~CLICK;

        const bool *keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_W])
            hardwareState |= FWD;
        else
            hardwareState &= ~FWD;

        if (keys[SDL_SCANCODE_SPACE])
            hardwareState |= JUMP;
        else
            hardwareState &= ~JUMP;

        if (keys[SDL_SCANCODE_A])
            hardwareState |= LEFT;
        else
            hardwareState &= ~LEFT;

        if (keys[SDL_SCANCODE_D])
            hardwareState |= RIGHT;
        else
            hardwareState &= ~RIGHT;
    }

    void preStep()
    {
        lastState = state;
        state = hardwareState | buffer;
        buffer = 0;
    }

    int wishdir()
    {
        int direction = 0;
        if (state & RIGHT)
            direction += 1;
        if (state & LEFT)
            direction += -1;
        return direction;
    }
}