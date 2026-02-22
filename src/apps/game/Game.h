#pragma once
#include "core/AppState.h"
#include <vector>

class Tickable;
class SolWorld;
class AppGame : public AppState
{
private:
    std::vector<Tickable *> tickables;
    SolWorld *world;
    int jumpCount;

public:
    int enemyCount = 500;
    AppGame(App *app);
    virtual void enter() override;
    virtual void step(double dt, double time) override;
    virtual void tick(double dt, double time, double alpha) override;
    virtual void exit();
};
