#pragma once
#include "core/AppState.h"
#include "miner/Miner.h"
#include <vector>

class Button;
class AppMining : public AppState
{
private:
    std::vector<Button*> buttons;
    std::string target;
    BitcoinHeader genesis;
    BitcoinMiner miner;
    MineResult result;

public:
    AppMining(App *app);
    virtual void enter(App *app) override;
    virtual void step(double dt) override;
    virtual void tick(double dt, double alpha) override;
};