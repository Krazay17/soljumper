#pragma once
#include "core/AppState.h"
#include "input/Input.h"
#include <iostream>
#include <functional>
#include <vector>
#include "graphics/Graphics.h"

class MenuButton
{
    SDL_FRect rect;
    std::function<void()> onClick;

public:
    MenuButton(float x, float y, float w, float h, std::function<void()> callback)
        : rect({x, y, w, h}), onClick(callback) {};

    void update();
    void render();
};

class AppMenu : public AppState
{
private:
    std::vector<MenuButton *> buttons;

public:
    virtual void enter(App *app) override;
    virtual void update(double dt) override;
    virtual void render(double alpha) override;

    virtual ~AppMenu()
    {
        for (auto &b : buttons)
            delete b;
        buttons.clear();
    }
};