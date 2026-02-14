#include "Mining.h"
#include <iostream>
#include <cstring>
#include "graphics/Graphics.h"
#include "logger/Logger.h"
#include "ui/Button.h"
#include "core/App.h"

AppMining::AppMining(App *app)
{
    buttons.push_back(new Button(0.0f, 0.0f, 100.0f, 50.0f, [app]()
                                 { app->changeAppState(AppStates::MENU); }, "Menu"));
    buttons.push_back(new Button(200.0f, 200.0f, 100.0f, 50.0f, [this]()
                                 { runMine(2); }, "Mine 2"));
    buttons.push_back(new Button(400.0f, 200.0f, 100.0f, 50.0f, [this]()
                                 { runMine(8); }, "Mine 8"));
    buttons.push_back(new Button(400.0f, 400.0f, 100.0f, 50.0f, [this]()
                                 { stopMine(); }, "Stop"));
}

AppMining::~AppMining()
{
    stopMine();
}

void AppMining::step(double dt)
{
    for (auto &b : buttons)
        b->update(dt);
}

void AppMining::tick(double dt, double alpha)
{
    for (auto &b : buttons)
        b->render();
    double price = Bitcoin::currentPrice.load();
    if (price <= 0.0)
        Gfx::drawText("Fetching BTC Price...", 0.0f, 100.0f);
    else
    {
        std::string priceText = "BTC: $" + std::to_string(price);
        Gfx::drawText(priceText.c_str(), 0.0f, 100.0f);
    }
}

void AppMining::exit()
{
    for (auto &b : buttons)
        b->reset();
}

void AppMining::stopMine()
{
    miner.stop();
    isMining = false;
}

void AppMining::runMine(int x)
{
    if (isMining)
        return;
    isMining = true;
    const std::string target = std::string(x, '0');
    genesis.nonce = 0;
    std::thread miningThread([this, target]()
                             {
                                 MineResult result;
                                 miner.run(genesis, target, result);
                                 if (result.found)
                                 {
                                     std::string foundstring = "Found coin!\n" + result.hash + "\nNonce: " + std::to_string(result.nonce);
                                     logToFile(foundstring);
                                     std::cout << "\n"
                                               << foundstring << std::endl;
                                               isMining = false;
                                 } });
    miningThread.detach();
}

void AppMining::enter(App *app)
{
    genesis.version = 1;
    memset(genesis.prev_hash, 0, 32);
    memset(genesis.merkle_root, 0xAA, 32);
    genesis.timestamp = 1231006505;
    genesis.bits = 0x1d00ffff;
}
