#include "Menu.h"

void MenuButton::update()
{
    bool hovering = (Input::mouseX >= rect.x && Input::mouseX <= rect.x + rect.w &&
                     Input::mouseY >= rect.y && Input::mouseY <= rect.y + rect.h);

    if (hovering && Input::actionMask & Actions::CLICK)
    {
        if (onClick)
            onClick();
    }
}

void MenuButton::render()
{
    SDL_Color red = {255, 0, 0, 255};
    Gfx::drawRect(rect.x, rect.y, rect.w, rect.h, red);
}

void AppMenu::enter(App *app)
{
    buttons.push_back(new MenuButton(100.0f, 100.0f, 50.0f, 50.0f, [app]()
                                     { std::cout << "Pressed Button!"; }));
}

void AppMenu::update(double dt)
{
    for (auto &b : buttons)
    {
        b->update();
    }
}

void AppMenu::render(double alpha)
{
    for (auto &b : buttons)
    {
        b->render();
    }
}