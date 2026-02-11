#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include "menu/Menu.h"
#include "graphics/Graphics.h"
#include <chrono>
#include "input/Input.h"

class App {
    private:
    static constexpr double dt = 1.0 / 240.0;
    bool running = true;
    public:
    void run();
};