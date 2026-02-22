#pragma once
#include "core/Ecs.h"
#include <string>
#include <functional>
#include "SDL3/SDL.h"
#include "input/Input.h"

class Element : public Tickable
{
protected:
    SDL_FRect rect;
    bool isHovered = false;
    bool isPressed = false;
    std::function<void()> onClick;
    std::string label;
    SDL_Color bgColor{100, 100, 100, 255};
    SDL_Color bgHoverColor{200, 200, 200, 255};
    SDL_Color textColor{255, 0, 0, 255};
    SDL_Color textHoverColor{255, 255, 255, 255};

public:
    Element(float x, float y, float w, float h, const char *t = "Button", std::function<void()> callback = NULL)
        : rect({x, y, w, h}), label(t), onClick(callback) {}
    virtual void step(double dt, double time) override
    {
        isHovered = (Input::mouseX >= rect.x && Input::mouseX <= rect.x + rect.w &&
                     Input::mouseY >= rect.y && Input::mouseY <= rect.y + rect.h);
        isPressed = isHovered && Input::held(CLICK);
        if (onClick && Input::pressed(CLICK))
            onClick();
    }
    virtual void tick(double dt, double time, double alpha) override = 0;
};