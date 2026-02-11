#pragma once
#include "core/Main.h"

class AppMenu : public AppState
{
    virtual void enter() override;
    virtual void update(double dt) override;
    virtual void render(double alpha) override;
};