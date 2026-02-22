#pragma once
#include "UiBase.h"
#include "graphics/Graphics.h"

class Slider : public Element
{

public:
    float value = 0.5f;
    std::function<void(float)> onSlide;

    Slider(float x, float y, float w, float h, std::function<void(float)> callback)
        : onSlide(callback), Element(x, y, w, h, "Slider") {}
    void step(double dt, double time) override
    {
        const float oldValue = value;
        Element::step(dt, time);
        if (isPressed)
            value = (Input::mouseX - rect.x) / rect.w;
        if (value < 0.0f)
            value = 0.0f;
        if (value > 1.0f)
            value = 1.0f;
        if (onSlide && oldValue != value)
            onSlide(value);
    }
    void tick(double dt, double time, double alpha) override
    {
        SDL_Color color = isHovered ? bgHoverColor : bgColor;
        Gfx::drawRect(rect.x, rect.y, rect.w, rect.h, color);
        const float handleWidth = rect.w / 10;
        Gfx::drawRect(rect.x + rect.w * value - handleWidth / 2, rect.y, rect.w / 10, rect.h, {255, 0, 0, 255});
    }
};