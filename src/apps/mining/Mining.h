#pragma once
#include "core/AppState.h"
#include "miner/Miner.h"
#include <vector>

class Button;
class App;
class AppMining : public AppState
{
private:
    std::vector<Button *> buttons;
    BitcoinHeader genesis;
    BitcoinMiner miner;
    MineResult result;
    double mineStartTime;
    std::string foundCoinString;
    bool hasLoggedFind = false;
    float limiter = 0.0f;
    std::string mineInfo;
    App *app;
public:
    bool isMining = false;
    AppMining(App *app);
    ~AppMining();
    virtual void enter() override;
    virtual void step(double dt, double time) override;
    virtual void tick(double dt, double time, double alpha) override;
    virtual void exit() override;
    void runMine(int x);
    void stopMine();
};