#include "Game.h"
#include <chrono>
#include <iostream>
#include "core/App.h"
#include "ui/Button.h"
#include "player/Player.h"
#include "core/SolWorld.h"

AppGame::AppGame(App *app)
{
    buttons.push_back(new Button(0.0f, 0.0f, 100.0f, 50.0f, [app]()
                                 { app->changeAppState(AppStates::MENU); }, "Menu"));
    player = new Player();
    world = new SolWorld();
}

void AppGame::enter(App *app)
{
}

void AppGame::step(double dt, double time)
{
    world->preStep(dt, time);
    world->step(dt, time);
    world->postStep(dt, time);
    for (auto *b : buttons)
        b->update();
    player->update(dt);
}

void AppGame::tick(double dt, double time, double alpha)
{
    world->tick(dt, time, alpha);
    for (auto *b : buttons)
        b->render();
    player->render(dt, alpha);
}

void AppGame::exit()
{
    for (auto *b : buttons)
        b->reset();
}
