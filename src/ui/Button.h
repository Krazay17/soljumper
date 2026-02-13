#pragma once
#include <functional>
#include "SDL3/SDL.h"
#include "math/Vec2.h"

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
    Vec2 getPos();
    Vec2 setPos(const Vec2 &vec);
};