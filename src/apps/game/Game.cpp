#include "Game.h"
#include <chrono>
#include <iostream>
#include "core/App.h"
#include "ui/Button.h"
#include "player/Player.h"
#include "core/SolWorld.h"
#include "movement/Movement.h"
#include "graphics/Graphics.h"
#include "core/PreFabs.h"

AppGame::AppGame(App *app)
{
}

void AppGame::enter()
{
    world = new SolWorld();

    int playerId = world->createEntity();
    world->localUsers.add(playerId);
    world->inputs.add(playerId);
    Comp::Physics &playerPhys = world->physics.add(playerId);
    playerPhys.x = 200.0f;
    playerPhys.y = 100.0f;
    playerPhys.w = 40.0f;
    playerPhys.h = 60.0f;
    playerPhys.type = BodyType::DYNAMIC;
    Comp::Sprite &playerSprite = world->sprites.add(playerId);
    playerSprite.width = 40.0f;
    playerSprite.height = 60.0f;
    playerSprite.color = {0, 0, 255, 255};

    for (int i = 0; i < enemyCount; ++i)
    {
        const float lat = std::sin(i) * 340 + 640;
        int id = Factory::makeEnemy(*world, lat, i * -1, 10.0f, 10.0f);
        world->gamePoints.add(id);
    }

    Factory::makeFloor(*world, 100.0f, 600.0f, 1080.0f, 15.0f);
    Factory::makeFloor(*world, 340.0f, 500.0f, 200.0f, 15.0f);
    Factory::makeFloor(*world, 740.0f, 500.0f, 200.0f, 15.0f);
    Factory::makeFloor(*world, 140.0f, 400.0f, 200.0f, 15.0f);
    Factory::makeFloor(*world, 940.0f, 400.0f, 200.0f, 15.0f);
    Factory::makeFloor(*world, 540.0f, 300.0f, 200.0f, 15.0f);
}

void AppGame::step(double dt, double time)
{
    world->preStep(dt, time);
    world->step(dt, time);
    world->postStep(dt, time);

    for (auto *b : buttons)
        b->update();
}

void AppGame::tick(double dt, double time, double alpha)
{
    Gfx::drawSprite(Gfx::loadTexture("assets/images/RedSky.webp"), 0, 0, 1280, 720);

    world->tick(dt, time, alpha);

    for (auto *b : buttons)
        b->render();
}

void AppGame::exit()
{
    for (auto *b : buttons)
        b->reset();

    delete world;
}
