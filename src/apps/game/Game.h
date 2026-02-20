#pragma once
#include "core/AppState.h"
#include <vector>

class Button;
class Player;
class SolWorld;
class AppGame : public AppState
{
private:
    std::vector<Button *> buttons;
    Player *player;
    SolWorld *world;
    int jumpCount;
    int enemyCount = 200;

public:
    AppGame(App *app);
    virtual void enter() override;
    virtual void step(double dt, double time) override;
    virtual void tick(double dt, double time, double alpha) override;
    virtual void exit();
};
