#pragma once

class AppState
{
public:
    virtual ~AppState() {}
    virtual void enter() {}
    virtual void update(double dt) = 0;
    virtual void render(double alpha) = 0;
};