#include "Ui.h"
#include "ui/Button.h"
#include "core/App.h"

AppUi::AppUi(App *app)
{
    buttons.push_back(
        new Button(500.0f, 500.0f, 50.0f, 50.0f, [app]() {}));
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
    for (auto *b : buttons)
        b->render();
}
