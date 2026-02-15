#pragma once
#include "math/Vec2.h"

class Movement
{
    void move(double dt);
    void applyGravity(float g);
    void applyCollision();
    void jump();
    float friction(double dt, float vel, float friction);
    float accelerate(double dt, float vel, int wishdir, float wishspeed, float accel);
    int wishdir();

public:
    float height = 50.0f;
    float width = 50.0f;
    float speed = 3.0f;
    float groundAccel = 14.0f;
    float groundFriction = 12.0f;
    float airAccel = 2.0f;
    float airFriction = 0.1f;
    float gravity = 9.81f;
    bool grounded = false;
    bool touchingLeft = false;
    bool touchingRight = false;
    Vec2 Velocity{0, 0};
    Vec2 pos{0, 0};

    float Floor = 720;
    float ceiling = 0;
    float LWall = 0;
    float RWall = 1280;
    Movement(float posX, float posY, float height = 50.0f, float width = 50.0f);
    void update(double dt);
};