#include "Game.h"
#include <iostream>
#include "core/App.h"
#include "ui/Button.h"

AppGame::AppGame(App *app)
{
    buttons.push_back(new Button(200.0f, 200.0f, 100.0f, 100.0f, [app]()
                                 { std::cout << "game button"; }));
    buttons.push_back(new Button(400.0f, 200.0f, 100.0f, 100.0f, [app]()
                                 { app->changeAppState(AppStates::MENU);}));
}

void AppGame::enter(App *app)
{
}

void AppGame::step(double dt)
{
    for (auto &b : buttons)
    {
        b->update();
    }
}

void AppGame::tick(double dt, double alpha)
{
    for (auto &b : buttons)
    {
        b->render();
    }
}
