#pragma once
#include "core/AppState.h"
#include <vector>

class Button;
class AppGame : public AppState
{
private:
    std::vector<Button *> buttons;

public:
    AppGame(App *app);
    virtual void enter(App *app) override;
    virtual void step(double dt) override;
    virtual void tick(double dt, double alpha) override;
};
