#include "Game.h"
#include <chrono>
#include <iostream>
#include "core/App.h"
#include "ui/Button.h"
#include "player/Player.h"
#include "core/SolWorld.h"
#include "movement/Movement.h"
#include "graphics/Graphics.h"

AppGame::AppGame(App *app)
{
    player = new Player();
    player->movement->onJump = [this]()
    {
        jumpCount++;
    };
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
    Gfx::drawSprite(Gfx::loadTexture("assets/images/RedSky.webp"), 0, 0, 1280, 720);
    world->tick(dt, time, alpha);
    for (auto *b : buttons)
        b->render();
    player->render(dt, alpha);
    std::string text = "Jumps: " + std::to_string(jumpCount);
    Gfx::drawText(text.c_str(), 600, 50);
}

void AppGame::exit()
{
    for (auto *b : buttons)
        b->reset();
}
