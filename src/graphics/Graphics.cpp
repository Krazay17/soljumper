#include "Graphics.h"

namespace Gfx
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Color bgColor = {0, 0, 0, 255};
    TTF_Font *mainFont = nullptr;

    bool init(const char *title, int w, int h)
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
            return false;

        if (!TTF_Init())
            return false;

        window = SDL_CreateWindow(title, w, h, 0);
        if (!window)
            return false;

        // NULL uses the default best driver (Vulkan/D3D11)
        renderer = SDL_CreateRenderer(window, NULL);
        if (!renderer)
            return false;

        mainFont = TTF_OpenFont("assets/fonts/MonaspaceKryptonFrozen-Bold.ttf", 24);
        if (!mainFont)
        {
            std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
        }

        return true;
    }

    void shutdown()
    {
        TTF_CloseFont(mainFont);
        TTF_Quit();
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

    void drawText(const char *text, float x, float y, SDL_Color color)
    {
        if (!mainFont || !text)
            return;

        // Create a surface from the string
        SDL_Surface *surf = TTF_RenderText_Blended(mainFont, text, 0, color);
        if (!surf)
            return;

        // Convert surface to texture
        SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);

        SDL_FRect dst = {x, y, (float)surf->w, (float)surf->h};

        // Draw it
        SDL_RenderTexture(renderer, tex, NULL, &dst);

        // CLEANUP: If you don't do this, you'll crash in 30 seconds
        SDL_DestroySurface(surf);
        SDL_DestroyTexture(tex);
    }
}