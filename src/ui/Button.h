#pragma once
#include <functional>
#include "SDL3/SDL.h"
#include "math/Vec2.h"

class Button
{
private:
    SDL_FRect rect;
    const char *text;
    std::function<void()> onClick;
    bool isHovered = false;
    bool wasClicked = false;
    float clickProgress = 0;
    SDL_Color bc;
    SDL_Color tc;

public:
    SDL_Color buttonColor{100, 100, 100, 255};
    SDL_Color buttonHoverColor{200, 200, 200, 255};
    SDL_Color textColor{255, 0, 0, 255};
    SDL_Color textHoverColor{255, 255, 255, 255};
    Button(float x, float y, float w, float h, std::function<void()> callback,
           const char *t = "Button");
    void update(const double dt = 0.016);
    void render();
    void reset();
    void clicked();
    Vec2 getPos();
    Vec2 setPos(const Vec2 &vec);
};