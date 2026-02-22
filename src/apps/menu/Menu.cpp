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

    auto *testButton = new Button({100.0f, 100.0f, 100.0f, 50.0f}, "Test");
    testButton->setOnClick([app]()
                           { std::cout << "BUTTON 1" << std::endl; });
    tickables.push_back(testButton);

    auto *mineButton = new Button({100.0f, 200.0f, 100.0f, 50.0f}, "Miner");
    mineButton->setOnClick([app]()
                           { app->changeAppState(AppStates::MINING); });
    tickables.push_back(mineButton);

    auto *gameButton = new Button({100.0f, 300.0f, 100.0f, 50.0f}, "Game");
    gameButton->setOnClick([app]()
                           { app->changeAppState(AppStates::GAME); });
    tickables.push_back(gameButton);

    auto *enemySlider = new Slider({200.0f, 400.0f, 200.0f, 50.0f}, "Enemies");
    enemySlider->setOnSlide(
        [app](Slider *self, float value)
        {
            const int e = static_cast<int>(value * 1000);
            static_cast<AppGame *>(app->getState(AppStates::GAME))->enemyCount = e;
            self->setText(std::to_string(e));
        });
    tickables.push_back(enemySlider);
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
