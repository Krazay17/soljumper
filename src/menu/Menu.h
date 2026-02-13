#pragma once
#include "core/AppState.h"
#include <functional>
#include "graphics/Graphics.h"
#include "ui/Button.h"

class AppMenu : public AppState
{
private:
    std::vector<Button *> buttons;

public:
    AppMenu(App *app);
    virtual void enter(App *app) override;
    virtual void step(double dt) override;
    virtual void tick(double dt, double alpha) override;

    virtual ~AppMenu()
    {
        for (auto &b : buttons)
            delete b;
        buttons.clear();
    }
};