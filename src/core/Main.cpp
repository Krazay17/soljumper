#include "Main.h"
#include <iostream>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include "menu/Menu.h"
#include "graphics/Graphics.h"

bool running = true;

int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        return -1;
    Gfx::window = SDL_CreateWindow("Jump Jump", 1280, 720, 0);

    Gfx::renderer = SDL_CreateRenderer(Gfx::window, NULL);

    AppState *currentState = new AppMenu();
    currentState->enter();

    const double dt = 1.0 / 60.0;
    double accumulator = 0;
    uint64_t lastTime = SDL_GetTicks();

    while (running)
    {
        uint64_t currentTime = SDL_GetTicks();
        double frameTime = (currentTime - lastTime) / 1000.0;
        lastTime = currentTime;
        accumulator += frameTime;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
                running = false;
        }
        while (accumulator >= dt)
        {
            currentState->update(dt);
            accumulator -= dt;
        }
        double alpha = accumulator / dt;
        SDL_SetRenderDrawColor(Gfx::renderer, 0, 0, 0, 255);
        SDL_RenderClear(Gfx::renderer);
        currentState->render(alpha);
        SDL_RenderPresent(Gfx::renderer);
    }
    delete currentState;
    SDL_Quit();
    return 0;
}