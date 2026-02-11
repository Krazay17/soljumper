#pragma once
#include <SDL3/SDL.h>

namespace Gfx {
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

    void drawRect(float x, float y, float w, float h, SDL_Color color);
};