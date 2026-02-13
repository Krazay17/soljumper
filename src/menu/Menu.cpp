#include "Menu.h"
#include "input/Input.h"
#include "core/App.h"
#include <iostream>
#include <vector>
#include "logger/Logger.h"
#include "math/Vec2.h"

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
    Bitcoin::fetchBitcoinPrice();
    buttons[0]->setPos(Vec2(100.0f, 100.0f));
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
    Vec2 target(500, 500);
    Vec2 nextPos = buttons[0]->getPos().lerp_fixed(target, 1, dt);
    buttons[0]->setPos(nextPos);
    for (auto &b : buttons)
    {
        b->render();
    }
    double price = Bitcoin::currentPrice.load();
    if (price <= 0.0)
    {
        Gfx::drawText("Fetching BTC Price...", 100.0f, 50.0f);
    }
    else
    {
        std::string priceText = "BTC: $" + std::to_string(price);
        Gfx::drawText(priceText.c_str(), 100.0f, 50.0f);
    }
}