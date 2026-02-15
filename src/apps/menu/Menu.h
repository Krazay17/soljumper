#pragma once
#include "core/AppState.h"
#include <vector>

class Button;
class AppMenu : public AppState
{
private:
    std::vector<Button *> buttons;

public:
    AppMenu(App *app);
    virtual void enter(App *app) override;
    virtual void step(double dt, double time) override;
    virtual void tick(double dt, double time, double alpha) override;
    virtual void exit() override;
};