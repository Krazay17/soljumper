#pragma once
#include <functional>
#include "SDL3/SDL.h"

class Button
{
private:
    SDL_FRect rect;
    std::function<void()> onClick;
    bool isHovered = false;

public:
    Button(float x, float y, float w, float h, std::function<void()> callback);
    void update();
    void render();
};