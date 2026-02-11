#include "Input.h"
#include <iostream>

namespace Input
{
    Uint32 actionMask = 0;
    Uint32 lastActionMask = 0;
    float mouseX = 0;
    float mouseY = 0;

    void update(SDL_Event event)
    {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                actionMask |= CLICK;
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                actionMask &= ~CLICK;
        }
    }
    void postUpdate()
    {
        lastActionMask = actionMask;
        // 1. Update Mouse Position
        SDL_GetMouseState(&mouseX, &mouseY);

        // 2. Update Continuous Keys
        const bool *keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_SPACE])
            actionMask |= JUMP;
        else
            actionMask &= ~JUMP;

        if (keys[SDL_SCANCODE_W]){
            actionMask |= FWD;
            std::cout << "FWD";
        }
        else
            actionMask &= ~FWD;
    }
}