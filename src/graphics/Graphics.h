#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace Gfx
{
    extern SDL_Window *window;
    extern SDL_Renderer *renderer;
    extern SDL_Color bgColor;
    extern TTF_Font *mainFont;
    extern int height;
    extern int width;
    bool init(const char *title, int w, int h);
    void shutdown();
    void clear();
    void render();
    void drawRect(float x, float y, float w, float h, SDL_Color color);
    void drawText(const char *text, float x, float y, SDL_Color color = {0, 255, 0, 255});
};