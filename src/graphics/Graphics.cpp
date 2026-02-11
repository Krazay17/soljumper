#include "Graphics.h"

namespace Gfx
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Color bgColor = {0, 0, 0, 255};

    bool init(const char *title, int w, int h)
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        {
            return false;
        }

        window = SDL_CreateWindow(title, w, h, 0);
        if (!window)
            return false;

        // NULL uses the default best driver (Vulkan/D3D11)
        renderer = SDL_CreateRenderer(window, NULL);
        if (!renderer)
            return false;

        return true;
    }

    void shutdown()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void clear()
    {
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);
    }

    void render()
    {
        SDL_RenderPresent(renderer);
    }

    void drawRect(float x, float y, float w, float h, SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_FRect r = {x, y, w, h};
        SDL_RenderFillRect(renderer, &r);
    }
}