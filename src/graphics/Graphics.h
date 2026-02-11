#pragma once
#include <SDL3/SDL.h>

namespace Gfx {
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;
    extern SDL_Color bgColor;
    bool init(const char* title, int w, int h);
    void shutdown();
    void clear();
    void render();
    void drawRect(float x, float y, float w, float h, SDL_Color color);
};