#pragma once
#include "core/AppState.h"
#include <vector>

class Tickable;
class AppMenu : public AppState
{
private:
    std::vector<Tickable *> tickables;
    App *app;

public:
    AppMenu(App *app);
    virtual void enter() override;
    virtual void step(double dt, double time) override;
    virtual void tick(double dt, double time, double alpha) override;
    virtual void exit() override;
};