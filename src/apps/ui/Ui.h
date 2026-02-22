#pragma once
#include "core/AppState.h"
#include <vector>

class Tickable;

class AppUi : public AppState
{
    std::vector<Tickable *> tickables;

public:
    AppUi(App *app);
    ~AppUi();
    void step(double dt, double time) override;
    void tick(double dt, double time, double alpha) override;
};