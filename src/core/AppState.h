#pragma once

class App;

class AppState
{
public:
    virtual void enter(App *app) {}
    virtual void step(double dt, double time) = 0;
    virtual void tick(double dt, double time, double alpha) = 0;
    virtual void exit() {}
};