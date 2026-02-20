#include "Mining.h"
#include <iostream>
#include <cstring>
#include "graphics/Graphics.h"
#include "logger/Logger.h"
#include "ui/Button.h"
#include "core/App.h"

AppMining::AppMining(App *app) : app(app)
{
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

void AppMining::step(double dt, double time)
{
    if (result.found && !hasLoggedFind)
    {
        stopMine();
        foundCoinString = "Found coin!\n" + result.hash + "\nNonce: " + std::to_string(result.nonce);
        logToFile(foundCoinString);
        std::cout << "\n"
                  << foundCoinString << std::endl;
        hasLoggedFind = true;
    }
    limiter += (float)dt;
    if (limiter > 1.0f)
    {
        limiter = 0.0f;
        const float elapsed = app->mstime - mineStartTime;
        const float hashes = (float)miner.getTotalHashes() / elapsed;
        mineInfo = "Hashrate: " + std::to_string(hashes) + " KH/s";
    }

    for (auto *b : buttons)
        b->update(dt);
}

void AppMining::tick(double dt, double time, double alpha)
{
    double price = Bitcoin::currentPrice.load();
    if (price <= 0.0)
        Gfx::drawText("Fetching BTC Price...", 0.0f, 100.0f);
    else
    {
        std::string priceText = "BTC: $" + std::to_string(price);
        Gfx::drawText(priceText.c_str(), 0.0f, 100.0f);
    }
    if (isMining)
    {
        Gfx::drawText(mineInfo.c_str(), 0.0f, 150.0f, {255, 0, 0, 255});
    }
    if(result.found)
    {
        Gfx::drawText(foundCoinString.c_str(), 0, 300.0f);
    }

    for (auto *b : buttons)
        b->render();
}

void AppMining::exit()
{
    for (auto *b : buttons)
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
    hasLoggedFind = false;
    result.found = false;
    result.hash = "";
    isMining = true;
    mineStartTime = app->mstime;
    genesis.nonce = 0;
    std::thread miningThread([this, x]()
                             { miner.run(genesis, std::string(x, '0'), std::ref(result)); });
    miningThread.detach();
}

void AppMining::enter()
{
    genesis.version = 1;
    memset(genesis.prev_hash, 0, 32);
    memset(genesis.merkle_root, 0xAA, 32);
    genesis.timestamp = 1231006505;
    genesis.bits = 0x1d00ffff;
}
