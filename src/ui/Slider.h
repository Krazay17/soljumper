#pragma once
#include "UiElement.h"
#include "graphics/Graphics.h"

class Slider : public UiElement
{

public:
    float value = 0.5f;
    std::function<void(float)> onSlide;

    Slider(float x, float y, float w, float h, std::function<void(float)> callback, const char *t = "Slider")
        : UiElement(x, y, w, h, NULL, t), onSlide(callback) {}
    void step(double dt, double time) override
    {
        UiElement::step(dt, time);
        
        const float oldValue = value;
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