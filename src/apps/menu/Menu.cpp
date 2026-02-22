#include "Menu.h"
#include "apps/game/Game.h"
#include "graphics/Graphics.h"
#include "input/Input.h"
#include "core/App.h"
#include <iostream>
#include <vector>
#include "logger/Logger.h"
#include "math/Vec2.h"
#include "ui/Button.h"
#include "ui/Slider.h"

AppMenu::AppMenu(App *app)
{
    this->app = app;
    tickables.push_back(new Button(100.0f, 100.0f, 100.0f, 50.0f, [app]()
                                   { std::cout << "BUTTON 1" << std::endl; }, "Test"));

    tickables.push_back(new Button(100.0f, 200.0f, 100.0f, 50.0f, [app]()
                                   { app->changeAppState(AppStates::MINING); }, "Miner"));

    tickables.push_back(new Button(100.0f, 300.0f, 100.0f, 50.0f, [app]()
                                   { app->changeAppState(AppStates::GAME); }, "Game"));

    tickables.push_back(new Slider(200.0f, 400.0f, 200.0f, 50.0f, [app](float value)
                                   { AppGame* game = static_cast<AppGame*>(app->getState(AppStates::GAME));
                                    game->enemyCount = value * 1000; }));
}

void AppMenu::enter()
{
    Bitcoin::fetchBitcoinPrice();
}

void AppMenu::step(double dt, double time)
{
    for (auto *t : tickables)
        t->step(dt, time);
}

void AppMenu::tick(double dt, double time, double alpha)
{
    for (auto *t : tickables)
        t->tick(dt, time, alpha);
}

void AppMenu::exit()
{
    for (auto *t : tickables)
        t->reset();
}
