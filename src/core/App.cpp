#include "App.h"
#include <iostream>
#include "input/Input.h"
#include <SDL3/SDL.h>
#include "graphics/Graphics.h"
#include <chrono>
#include "apps/menu/Menu.h"
#include "apps/game/Game.h"
#include "apps/mining/Mining.h"
#include "apps/ui/Ui.h"
#include "math/Utils.h"

App::App()
{
    AppReg[AppStates::MENU] = new AppMenu(this);
    AppReg[AppStates::GAME] = new AppGame(this);
    AppReg[AppStates::MINING] = new AppMining(this);

    PersistApps.push_back(new AppUi(this));
}

void App::run()
{
    if (!Gfx::init("Sol Jumper", 1280, 720))
    {
        std::cerr << "Graphics failed to initialize" << SDL_GetError() << std::endl;
        return;
    }
    currentState = AppReg[AppStates::MENU];
    currentState->enter();

    using clock = std::chrono::steady_clock;
    double accumulator = 0;
    auto startTime = clock::now();
    auto lastTime = startTime;
    while (running)
    {
        auto currentTime = clock::now();

        std::chrono::duration<double, std::milli> duration = currentTime - startTime;
        mstime = duration.count();

        std::chrono::duration<double> elapsed = currentTime - lastTime;
        double frameTime = elapsed.count();
        if (frameTime > 0.25)
            frameTime = 0.25;
        lastTime = currentTime;
        accumulator += frameTime;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
                changeAppState(AppStates::MENU);
            Input::handleEvent(event);
            if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
            }
        }
        Input::update();

        while (accumulator >= App::dt)
        {
            Input::preStep();
            currentState->step(App::dt, mstime);
            for (auto *a : PersistApps)
                a->step(dt, mstime);
            accumulator -= App::dt;
        }

        Gfx::clear();
        const double alpha = accumulator / App::dt;
        currentState->tick(frameTime, mstime, alpha);
        for (auto *a : PersistApps)
            a->tick(dt, mstime, alpha);
        if (showFps)
            printFps(frameTime);
        Gfx::render();
    }
    for (auto [a, b] : AppReg)
    {
        delete b;
    }
    Gfx::shutdown();
}

void App::changeAppState(AppStates state)
{
    if (AppReg[state] == currentState)
        return;
    if (!AppReg[state])
        return;
    currentState->exit();
    currentState = AppReg[state];
    currentState->enter();
}

void App::printFps(double frameTime)
{
    const float currentFps = (frameTime > 0.0f) ? 1.0f / (float)frameTime : 0.0f;
    if (std::isfinite(currentFps))
    {
        smoothedFps = lerp(smoothedFps, currentFps, 6.0f, (float)frameTime);
    }
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "FPS: %d", static_cast<int>(smoothedFps));
    Gfx::drawText(buffer, 0, 50, {255, 255, 255, 255});
}

void App::toggleFps()
{
}

AppState *App::getState(AppStates state)
{
    return AppReg[state];
}
