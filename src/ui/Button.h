#pragma once
#include "ui/UiElement.h"
#include "SDL3/SDL.h"
#include "math/Utils.h"
#include "graphics/Graphics.h"

class Button : public UiElement
{
public:
    Button(float x, float y, float w, float h, std::function<void()> callback, const char *t = "Button")
        : UiElement(x, y, w, h, callback, t) {}
    void step(double dt, double time) override
    {
        UiElement::step(dt, time);
    }

    void tick(double dt, double time, double alpha) override
    {
        if (clickProgress > 0)
        {
            bc.r = lerp_linear(0.0f, bgHoverColor.r, clickProgress);
            bc.g = lerp_linear(0.0f, 255.0f, clickProgress);
            bc.b = lerp_linear(0.0f, bgHoverColor.b, clickProgress);
        }
        else
        {
            bc = isHovered ? bgHoverColor : bgColor;
        }
        tc = isHovered ? textHoverColor : textColor;
        Gfx::drawRect(rect.x, rect.y, rect.w, rect.h, bc);
        std::string tString = text;
        float textX = (rect.x + rect.w / 2) - tString.length() * 8;
        float textY = rect.y + rect.h / 5;
        Gfx::drawText(text, textX, textY, tc);
    }
};