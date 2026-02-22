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
    buttons.push_back(new Button(100.0f, 100.0f, 100.0f, 50.0f, [app]()
                                 { std::cout << "BUTTON 1" << std::endl; }, "Test"));

    buttons.push_back(new Button(100.0f, 200.0f, 100.0f, 50.0f, [app]()
                                 { app->changeAppState(AppStates::MINING); }, "Miner"));

    buttons.push_back(new Button(100.0f, 300.0f, 100.0f, 50.0f, [app]()
                                 { app->changeAppState(AppStates::GAME); }, "Game"));

    tickables.push_back(new Slider(200.0f, 400.0f, 200.0f, 50.0f, [app](float value)
                                   { AppGame* game = static_cast<AppGame*>(app->getState(AppStates::GAME));
                                    game->enemyCount = value * 1000; }));
}

void AppMenu::enter()
{
    Bitcoin::fetchBitcoinPrice();
    buttons[0]->setPos(Vec2(100.0f, 100.0f));
}

void AppMenu::step(double dt, double time)
{
    for (auto *t : tickables)
        t->step(dt, time);

    for (auto *b : buttons)
        b->update();
}

void AppMenu::tick(double dt, double time, double alpha)
{
    for (auto *t : tickables)
        t->tick(dt, time, alpha);

    Vec2 target(900, 500);
    Vec2 nextPos = buttons[0]->getPos().lerp_fixed(target, 1, dt);
    buttons[0]->setPos(nextPos);

    for (auto *b : buttons)
        b->render();
}

void AppMenu::exit()
{
    for (auto *b : buttons)
        b->reset();
}
