#pragma once
#include <cstdint>
#include "Components.h"

class SolWorld;

enum SystemFlags
{
    HAS_PRESTEP = 1 << 0,
    HAS_STEP = 1 << 1,
    HAS_POSTSTEP = 1 << 2,
    HAS_TICK = 1 << 3,
};

class EcsSystem
{
public:
    uint8_t flags = 0;
    uint8_t required = 0;
    virtual void enter() {};
    virtual void preStep(SolWorld &world, double dt, double time) {};
    virtual void step(SolWorld &world, double dt, double time) {};
    virtual void postStep(SolWorld &world, double dt, double time) {};
    virtual void tick(SolWorld &world, double dt, double time, double alpha) {};
};

class Tickable
{
    public:
    virtual void step(double dt, double time) = 0;
    virtual void tick(double dt, double time, double alpha) = 0;
};