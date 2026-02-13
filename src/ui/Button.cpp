#include "Button.h"
#include "input/Input.h"
#include "graphics/Graphics.h"

Button::Button(float x, float y, float w, float h, std::function<void()> callback)
    : rect({x, y, w, h}), onClick(callback) {}

void Button::update()
{
    // Check collision between mouse and button rect (AABB)
    isHovered = (Input::mouseX >= rect.x && Input::mouseX <= rect.x + rect.w &&
                 Input::mouseY >= rect.y && Input::mouseY <= rect.y + rect.h);

    if (isHovered && Input::pressed(CLICK))
    {
        if (onClick) onClick();
    }
}

void Button::render()
{
    // Simple visual feedback: Change color when hovering
    SDL_Color color = isHovered ? SDL_Color{200, 200, 200, 255} : SDL_Color{100, 100, 100, 255};
    
    Gfx::drawRect(rect.x, rect.y, rect.w, rect.h, color);
}