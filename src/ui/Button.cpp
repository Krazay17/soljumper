#include "Button.h"
#include "math/Utils.h"
#include <string>
#include <iostream>
#include "input/Input.h"
#include "graphics/Graphics.h"

Button::Button(float x, float y, float w, float h, std::function<void()> callback, const char *t)
    : rect({x, y, w, h}), onClick(callback), text(t) {}

void Button::update(const double dt)
{
    // Check collision between mouse and button rect (AABB)
    isHovered = (Input::mouseX >= rect.x && Input::mouseX <= rect.x + rect.w &&
                 Input::mouseY >= rect.y && Input::mouseY <= rect.y + rect.h);

    if (isHovered && Input::pressed(CLICK))
        clicked();

    if (wasClicked)
    {
        clickProgress += dt * 8;
        if (clickProgress >= 1)
        {
            reset();
        }
    }
}

void Button::clicked()
{
    wasClicked = true;
    clickProgress = 0;
    if (onClick)
        onClick();
}

void Button::reset()
{
    isHovered = false;
    wasClicked = false;
    clickProgress = 0;
}

void Button::render()
{
    if (wasClicked)
    {
        bc.r = lerp_linear(buttonHoverColor.r, 0.0f, clickProgress);
        bc.g = lerp_linear(255.0f, 0.0f, clickProgress);
        bc.b = lerp_linear(buttonHoverColor.b, 0.0f, clickProgress);
    }
    else
    {
        bc = isHovered ? buttonHoverColor : buttonColor;
    }
    tc = isHovered ? textHoverColor : textColor;
    Gfx::drawRect(rect.x, rect.y, rect.w, rect.h, bc);
    std::string tString = text;
    float textX = (rect.x + rect.w / 2) - tString.length() * 8;
    float textY = rect.y + rect.h / 5;
    Gfx::drawText(text, textX, textY, tc);
}

Vec2 Button::getPos()
{
    return Vec2(rect.x, rect.y);
}

Vec2 Button::setPos(const Vec2 &vec)
{
    rect.x = vec.x;
    rect.y = vec.y;
    return Vec2(vec.x, vec.y);
}
