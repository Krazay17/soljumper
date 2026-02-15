#include "Game.h"
#include <iostream>
#include "core/App.h"
#include "ui/Button.h"
#include "player/Player.h"

AppGame::AppGame(App *app)
{
    buttons.push_back(new Button(0.0f, 0.0f, 100.0f, 50.0f, [app]()
                                 { app->changeAppState(AppStates::MENU); }, "Menu"));
    player = new Player();
    
}

void AppGame::enter(App *app)
{
}

void AppGame::step(double dt)
{
    for (auto &b : buttons)
        b->update();
    player->update(dt);
}

void AppGame::tick(double dt, double alpha)
{
    for (auto &b : buttons)
        b->render();
    player->render();
}

void AppGame::exit()
{
    for (auto &b : buttons)
        b->reset();
}
