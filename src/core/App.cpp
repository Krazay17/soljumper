#include "App.h"
#include <iostream>
#include "menu/Menu.h"
#include "game/Game.h"
#include "input/Input.h"
#include <SDL3/SDL.h>
#include "graphics/Graphics.h"
#include <chrono>

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
        Gfx::render();
    }
    delete currentState;
    Gfx::shutdown();
}

void App::fillRegistry()
{
    AppReg[AppStates::MENU] = new AppMenu(this);
    AppReg[AppStates::GAME] = new AppGame(this);
}

void App::changeAppState(AppStates state)
{
    currentState = AppReg[state];
    currentState->enter(this);
}
