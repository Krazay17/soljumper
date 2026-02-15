#include "Movement.h"
#include <cmath>
#include "input/Input.h"
#include "math/Vec2.h"

void Movement::move(double dt)
{
    const float f = grounded ? groundFriction : airFriction;
    const float a = grounded ? groundAccel : airAccel;
    Velocity.x = friction(dt, Velocity.x, f);
    Velocity.x = accelerate(dt, Velocity.x, wishdir(), speed, a);
    if (grounded)
        jump();
}

void Movement::jump()
{
    if (Input::pressed(Actions::JUMP))
    {
        Velocity.y = -4;
    }
}

float Movement::friction(double dt, float vel, float friction)
{
    const float speed = std::abs(vel);
    if (speed < 0.01f)
        return 0.0f;
    const float drop = speed * friction * dt;
    const float newSpeed = std::max(0.0f, speed - drop);
    return vel * (newSpeed / speed);
}

float Movement::accelerate(double dt, float vel, int wishdir, float wishspeed, float accel)
{
    const float dirSpeed = vel * wishdir;
    const float addSpeed = wishspeed - dirSpeed;
    if (addSpeed <= 0)
        return vel;
    const float accelSpeed = accel * wishspeed * dt;
    const float final = std::min(accelSpeed, addSpeed);
    return vel + (wishdir * final);
}

int Movement::wishdir()
{
    int direction = 0;
    if (Input::held(Actions::LEFT))
        direction -= 1;
    if (Input::held(Actions::RIGHT))
        direction += 1;
    return direction;
}

Movement::Movement(float posX, float posY, float h, float w)
    : pos{posX, posY}, height(h), width(w)
{
}

void Movement::update(double dt)
{
    applyGravity(gravity * dt);
    move(dt);
    pos += Velocity;
    applyCollision();
}

void Movement::applyGravity(float g)
{
    if (!grounded)
        Velocity.y += g;
    else
        Velocity.y = 0;
}

void Movement::applyCollision()
{
    float floor = Floor - height;
    float rWall = RWall - width;
    if (pos.y < floor)
    {
        grounded = false;
    }
    if (pos.y >= floor)
    {
        pos.y = floor;
        grounded = true;
    }
    if (pos.x <= LWall)
    {
        pos.x = LWall;
        touchingLeft = true;
        Velocity.x = 0;
    }
    else
        touchingLeft = false;
    if (pos.x >= rWall)
    {
        pos.x = rWall;
        touchingRight = true;
        Velocity.x = 0;
    }
    else
        touchingRight = false;
}
