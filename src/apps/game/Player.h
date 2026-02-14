#pragma once
#include "math/Vec2.h"

class Player
{
    float speed = 2;
    float gravity = 9.81;
    Vec2 velocity{0,0};
    Vec2 pos{0, 0};
    float height = 50.0f;
    float width = 50.0f;

    void move(double dt);
    void walk();
    void jump();
    void applyGravity(float g);

public:
    void render();
    void update(double dt);
};