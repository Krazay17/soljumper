#include "Mining.h"
#include <iostream>
#include <cstring>
#include "logger/Logger.h"
#include "ui/Button.h"
#include "core/App.h"

AppMining::AppMining(App *app)
{
    buttons.push_back(new Button(200.0f, 200.0f, 200.0f, 200.0f, [app]() {
        app->changeAppState(AppStates::MENU);
    }));
}

void AppMining::step(double dt)
{
}

void AppMining::tick(double dt, double alpha)
{
}

void AppMining::enter(App *app)
{
    genesis.version = 1;
    memset(genesis.prev_hash, 0, 32);
    memset(genesis.merkle_root, 0xAA, 32);
    genesis.timestamp = 1231006505;
    genesis.bits = 0x1d00ffff;
    genesis.nonce = 0;

    miner.run(genesis, target, result);
    if (result.found)
    {
        std::string foundstring = "Found coin!\n" + result.hash + "\nNonce: " + std::to_string(result.nonce);
        logToFile(foundstring);
        std::cout << "\n"
                  << foundstring << std::endl;
    }
}
