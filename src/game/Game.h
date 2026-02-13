#pragma once
#include "core/AppState.h"
#include <vector>
#include "ui/Button.h"

class AppGame : public AppState
{
    private:
    std::vector<Button*> buttons;
    public:
    AppGame(App *app);
    void enter(App *app);
    void step(double dt);
    void tick(double dt, double alpha);
};
