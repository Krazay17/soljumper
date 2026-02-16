#pragma once
#include "math/Vec2.h"
#include "math/Utils.h"

class Movement;
class Player
{
    Vec2 pos{0,0};
    float height = 50.0f;
    float width = 50.0f;
    
    public:
    Movement *movement;
    Player();
    void render(double dt, double alpha);
    void update(double dt);
};