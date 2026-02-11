#include "App.h"

void App::run()
{
    if (!Gfx::init("Sol Jumper", 1280, 720))
    {
        std::cerr << "Graphics failed to initialize" << SDL_GetError() << std::endl;
        return;
    }
    AppState *currentState = new AppMenu();
    currentState->enter(this);

    double accumulator = 0;
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (running)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastTime;
        double frameTime = elapsed.count();
        lastTime = currentTime;
        accumulator += frameTime;
        // std::cout << frameTime << std::endl;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
                running = false;
            Input::update(event);
        }
        while (accumulator >= App::dt)
        {
            currentState->update(App::dt);
            accumulator -= App::dt;
        }
        Input::postUpdate();
        double alpha = accumulator / App::dt;
        Gfx::clear();
        currentState->render(alpha);
        Gfx::render();
    }
    delete currentState;
    Gfx::shutdown();
}