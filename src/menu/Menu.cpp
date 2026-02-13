#include "Menu.h"
#include "input/Input.h"
#include "core/App.h"
#include <iostream>
#include <vector>

AppMenu::AppMenu(App *app)
{
    buttons.push_back(new Button(100.0f, 100.0f, 50.0f, 50.0f, [app]()
                                     { std::cout << "BUTTON 1" << std::endl; }));

    buttons.push_back(new Button(100.0f, 200.0f, 50.0f, 50.0f, [app]()
                                     { std::cout << "BUTTON 2" << std::endl; }));

    buttons.push_back(new Button(100.0f, 300.0f, 50.0f, 50.0f, [app]()
                                     { app->changeAppState(AppStates::GAME); }));
}

void AppMenu::enter(App *app)
{
}

void AppMenu::step(double dt)
{
    for (auto &b : buttons)
    {
        b->update();
    }
}

void AppMenu::tick(double dt, double alpha)
{
    for (auto &b : buttons)
    {
        b->render();
    }
}