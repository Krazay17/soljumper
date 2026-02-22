#pragma once
#include "core/Ecs.h"
#include <string>
#include <cmath>
#include <functional>
#include "SDL3/SDL.h"
#include "input/Input.h"
#include "math/Vec2.h"

class UiElement : public Tickable
{
protected:
    bool isHovered = false;
    bool isPressed = false;
    float clickProgress = 0;
    float progressSpeed = 1;
    const char *text;

    std::function<void()> onClick;

    SDL_FRect rect;
    SDL_Color bc;
    SDL_Color tc;
    SDL_Color bgColor{100, 100, 100, 255};
    SDL_Color bgHoverColor{200, 200, 200, 255};
    SDL_Color textColor{255, 0, 0, 255};
    SDL_Color textHoverColor{255, 255, 255, 255};

public:
    UiElement(float x, float y, float w, float h, std::function<void()> callback = NULL, const char *t = "Button")
        : rect({x, y, w, h}), onClick(callback), text(t) {}
    virtual void step(double dt, double time) override
    {
        isHovered = (Input::mouseX >= rect.x && Input::mouseX <= rect.x + rect.w &&
                     Input::mouseY >= rect.y && Input::mouseY <= rect.y + rect.h);
        isPressed = isHovered && Input::held(CLICK);

        if (clickProgress > 0)
            clickProgress = std::max(0.0f, clickProgress -= dt * progressSpeed);

        if (isPressed)
            clickProgress = 1.0f;

        if (onClick && isHovered && Input::pressed(CLICK))
            onClick();
    }
    virtual void tick(double dt, double time, double alpha) override = 0;

    Vec2 getPos()
    {
        return Vec2(rect.x, rect.y);
    }
    Vec2 setPos(const Vec2 &vec)
    {
        rect.x = vec.x;
        rect.y = vec.y;
        return Vec2(vec.x, vec.y);
    }
    virtual void reset() override
    {
        clickProgress = 0;
    }
};