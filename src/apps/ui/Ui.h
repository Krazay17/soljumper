#pragma once
#include "core/AppState.h"
#include <vector>

class Button;
class AppUi : public AppState
{
    std::vector<Button *> buttons;

public:
    AppUi(App *app);
    ~AppUi();
    void step(double dt, double time);
    void tick(double dt, double time, double alpha);
};