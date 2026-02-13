#pragma once

class App;

class AppState
{
public:
    virtual ~AppState() {}
    virtual void enter(App *app) {}
    virtual void step(double dt) = 0;
    virtual void tick(double dt, double alpha) = 0;
};