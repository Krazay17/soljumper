#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>

namespace Gfx
{
    struct CachedText
    {
        SDL_Texture *texture;
        int w, h;
    };
    extern std::unordered_map<std::string, CachedText> textCache;

    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
    extern SDL_Texture *texture;
    extern SDL_Color bgColor;
    extern TTF_Font *mainFont;
    extern int height;
    extern int width;
    extern int clearAccumulator;
    bool init(const char *title, int w, int h);
    void shutdown();
    void clear();
    void render();
    void drawRect(float x, float y, float w, float h, SDL_Color color);
    void drawText(const char *text, float x, float y, SDL_Color color = {0, 255, 0, 255});
    void clearTextCache();
    void drawSprite(SDL_Texture *tex, float x, float y, float w, float h);
    SDL_Texture *loadTexture(const char *path);
    SDL_HitTestResult HitTest(SDL_Window *win, const SDL_Point *area, void *data);
};