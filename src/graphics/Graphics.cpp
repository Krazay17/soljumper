#include "Graphics.h"
#include "SDL3_image/SDL_image.h"

namespace Gfx
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *texture = nullptr;
    SDL_Color bgColor = {0, 0, 0, 255};
    TTF_Font *mainFont = nullptr;
    std::unordered_map<std::string, CachedText> textCache;
    std::unordered_map<std::string, SDL_Texture *> texCache;
    int height;
    int width;
    int clearAccumulator = 0;

    bool init(const char *title, int w, int h)
    {
        height = h;
        width = w;
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
            return false;

        if (!TTF_Init())
            return false;

        window = SDL_CreateWindow(title, w, h, SDL_WINDOW_BORDERLESS);
        if (!window)
            return false;
        SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
        SDL_SetWindowHitTest(window, HitTest, nullptr);

        // NULL uses the default best driver (Vulkan/D3D11)
        renderer = SDL_CreateRenderer(window, NULL);
        if (!renderer)
            return false;

        SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_DISABLED);

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
        clearAccumulator++;
        if (clearAccumulator > 5000)
        {
            clearAccumulator = 0;
            clearTextCache();
        }
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
        if (!mainFont || !text || text[0] == '\0')
            return;

        // Create a unique key for this specific text + color
        // (Color is included so if you change color, it redraws)
        std::string key = std::string(text) + std::to_string(color.r) + std::to_string(color.g) + std::to_string(color.b);

        SDL_Texture *tex = nullptr;
        float w, h;

        if (textCache.find(key) == textCache.end())
        {
            // NOT in cache - Create it once
            SDL_Surface *surf = TTF_RenderText_Blended(mainFont, text, 0, color);
            if (!surf)
                return;

            tex = SDL_CreateTextureFromSurface(renderer, surf);
            textCache[key] = {tex, surf->w, surf->h};

            w = (float)surf->w;
            h = (float)surf->h;
            SDL_DestroySurface(surf);
        }
        else
        {
            // FOUND in cache - Fast path!
            tex = textCache[key].texture;
            w = (float)textCache[key].w;
            h = (float)textCache[key].h;
        }

        SDL_FRect dst = {x, y, w, h};
        SDL_RenderTexture(renderer, tex, NULL, &dst);
    }

    void clearTextCache()
    {
        for (auto &pair : textCache)
        {
            SDL_DestroyTexture(pair.second.texture);
        }
        textCache.clear();
    }

    SDL_Texture *loadTexture(const char *path)
    {
        std::string key(path);
        if (texCache.find(key) != texCache.end())
            return texCache[key];

        SDL_Texture *newTex = IMG_LoadTexture(renderer, path);
        if (!newTex)
        {
            std::cout << "IMG Error: " << SDL_GetError() << " Path: " << path << std::endl;
            return nullptr;
        }
        texCache[key] = newTex;
        return newTex;
    }

    void drawSprite(SDL_Texture *tex, float x, float y, float w, float h)
    {
        if (!tex)
            return;

        SDL_FRect dst = {x, y, w, h};
        // NULL for the second parameter means "draw the whole source image"
        SDL_RenderTexture(renderer, tex, NULL, &dst);
    }

    SDL_HitTestResult HitTest(SDL_Window *win, const SDL_Point *area, void *data)
    {
        if (area->y < 30 && area->x > 100 && area->x < width - 100)
        {
            return SDL_HITTEST_DRAGGABLE;
        }
        return SDL_HITTEST_NORMAL;
    }
}