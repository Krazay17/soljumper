#pragma once

class App;

class AppState
{
public:
    virtual ~AppState() {}
    virtual void enter(App *app) {}
    virtual void update(double dt) = 0;
    virtual void render(double alpha) = 0;
};