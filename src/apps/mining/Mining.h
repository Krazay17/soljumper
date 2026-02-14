#pragma once
#include "core/AppState.h"
#include "miner/Miner.h"
#include <vector>

class Button;
class AppMining : public AppState
{
private:
    std::vector<Button *> buttons;
    BitcoinHeader genesis;
    BitcoinMiner miner;

public:
    bool isMining = false;
    AppMining(App *app);
    virtual ~AppMining() override;
    virtual void enter(App *app) override;
    virtual void step(double dt) override;
    virtual void tick(double dt, double alpha) override;
    virtual void exit() override;
    void runMine(int x);
    void stopMine();
};