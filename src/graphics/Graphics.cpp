#include "Graphics.h"

namespace Gfx
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    void drawRect(float x, float y, float w, float h, SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_FRect r = {x, y, w, h};
        SDL_RenderFillRect(renderer, &r);
    }
}