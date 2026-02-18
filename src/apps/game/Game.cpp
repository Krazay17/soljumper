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
    world = new SolWorld();

    int playerId = world->createEntity();
    world->localUsers.add(playerId);
    world->inputs.add(playerId);
    Comp::Position &playerPos = world->positions.add(playerId);
    playerPos.x = 400.0f;
    playerPos.y = 400.0f;
    world->sprites.add(playerId).color = {0,0,255,255};
    world->velocities.add(playerId);
    Comp::Body &playerBody = world->bodies.add(playerId);
    playerBody.type = BodyType::DYNAMIC;

    int enemyId = world->createEntity();
    Comp::Position &ePos = world->positions.add(enemyId);
    ePos.x = 500.0f;
    ePos.y = 550.0f;
    world->sprites.add(enemyId);
    world->velocities.add(enemyId);
    world->bodies.add(enemyId);

    int floorId = world->createEntity();
    Comp::Position &floorPos = world->positions.add(floorId);
    floorPos.x = 100.0f;
    floorPos.y = 600.0f;
    Comp::Sprite &floorSprite = world->sprites.add(floorId);
    floorSprite.color = {0, 255, 0, 255};
    floorSprite.width = 1080.0f;
    floorSprite.height = 25.0f;
    Comp::Body &floorBody = world->bodies.add(floorId);
    floorBody.width = 1080.0f;
    floorBody.height = 25.0f;

    // player = new Player();
    if (player)
        player->movement->onJump = [this]()
        {
            jumpCount++;
        };
}

void AppGame::enter(App *app)
{
}

void AppGame::step(double dt, double time)
{
    world->preStep(dt, time);
    world->step(dt, time);
    world->postStep(dt, time);

    if (player)
        player->update(dt);

    for (auto *b : buttons)
        b->update();
}

void AppGame::tick(double dt, double time, double alpha)
{
    Gfx::drawSprite(Gfx::loadTexture("assets/images/RedSky.webp"), 0, 0, 1280, 720);

    world->tick(dt, time, alpha);

    std::string text = "Jumps: " + std::to_string(jumpCount);
    Gfx::drawText(text.c_str(), 600, 50);

    if (player)
        player->render(dt, alpha);

    for (auto *b : buttons)
        b->render();
}

void AppGame::exit()
{
    for (auto *b : buttons)
        b->reset();
}
