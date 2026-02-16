#include "Ui.h"
#include "ui/Button.h"
#include "core/App.h"
#include "graphics/Graphics.h"

AppUi::AppUi(App *app)
{
    buttons.push_back(
        new Button(0.0f, 0.0f, 100.0f, 50.0f, [app]()
                   { app->changeAppState(AppStates::MENU); }, "Menu"));
    buttons.push_back(
        new Button(1180.0f, 0.0f, 100.0f, 50.0f, [app]()
                   { app->exitApp(); }, "Exit"));
}

AppUi::~AppUi()
{
    for (auto *b : buttons)
        delete b;
}

void AppUi::step(double dt, double time)
{
    for (auto *b : buttons)
        b->update();
}

void AppUi::tick(double dt, double time, double alpha)
{
    // Draw a dark gray bar at the top
    Gfx::drawRect(0, 0, 1280, 30, {40, 40, 40, 255});

    // Draw the Title
    Gfx::drawText("Sol Jumper - Alpha", 200, 0, {200, 200, 200, 255});

    for (auto *b : buttons)
        b->render();
}
