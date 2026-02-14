#include "App.h"
#include <iostream>
#include "input/Input.h"
#include <SDL3/SDL.h>
#include "graphics/Graphics.h"
#include <chrono>
#include "apps/menu/Menu.h"
#include "apps/game/Game.h"
#include "apps/mining/Mining.h"
#include "math/Utils.h"

void App::run()
{
    if (!Gfx::init("Sol Jumper", 1280, 720))
    {
        std::cerr << "Graphics failed to initialize" << SDL_GetError() << std::endl;
        return;
    }
    fillRegistry();
    currentState = AppReg[AppStates::MENU];
    currentState->enter(this);

    double accumulator = 0;
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastTime;
        const double frameTime = elapsed.count();
        lastTime = currentTime;
        accumulator += frameTime;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
                running = false;
            Input::handleEvent(event);
        }
        Input::update();
        while (accumulator >= App::dt)
        {
            Input::preStep();
            currentState->step(App::dt);
            accumulator -= App::dt;
        }
        const double alpha = accumulator / App::dt;
        Gfx::clear();
        currentState->tick(frameTime, alpha);
        if (showFps)
        {
            // Add 'float smoothedFps' as a member variable to your App class
            // Then inside run():
            const float currentFps = 1.0f / frameTime;
            if (std::isfinite(currentFps))
            {
                smoothedFps = lerp(smoothedFps, currentFps, 6.0f, (float)frameTime);
            }
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "FPS: %d", static_cast<int>(smoothedFps));
            Gfx::drawText(buffer, 0, 50, {255, 255, 255, 255});
        }
        Gfx::render();
    }
    for (auto [a, b] : AppReg)
    {
        delete b;
    }
    Gfx::shutdown();
}

void App::fillRegistry()
{
    AppReg[AppStates::MENU] = new AppMenu(this);
    AppReg[AppStates::GAME] = new AppGame(this);
    AppReg[AppStates::MINING] = new AppMining(this);
}

void App::changeAppState(AppStates state)
{
    currentState->exit();
    currentState = AppReg[state];
    currentState->enter(this);
}

void App::toggleFps()
{
}
