#include "Menu.h"
#include <iostream>
#include "graphics/Graphics.h"

void AppMenu::enter()
{
    std::cout << "Entered Menu";
}

void AppMenu::update(double dt)
{
}

void AppMenu::render(double alpha)
{
    SDL_Color red = {255, 0, 0, 255};
    Gfx::drawRect(100.0f, 100.0f, 50.0f, 50.0f, red);
}