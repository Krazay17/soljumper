#pragma once
#include "math/Vec2.h"
#include <SDL3/SDL.h>
#include <iostream>

enum ComponentBit
{
    POSITION = 1 << 0,
    VELOCITY = 1 << 1,
};

struct Position
{
    float x, y;
};

struct User
{
    std::string name = "Player";
};

struct InputComp
{
    int wishDirX = 0;
    int wishDirY = 0;
    bool jumpRequested = false;
};

struct Velocity
{
    float vx, vy;
    float wishdir;
    float speed = 10;
    float accel = 10;
};

enum BodyShape
{
    BOX
};
enum BodyType
{
    STATIC,
    DYNAMIC
};
enum BodyTouching
{
    TOUCHING_DOWN = 1,
    TOUCHING_UP = 1 << 1,
    TOUCHING_LEFT = 1 << 2,
    TOUCHING_RIGHT = 1 << 3,
};
struct Body
{
    BodyShape shape = BodyShape::BOX;
    BodyType type = BodyType::STATIC;
    uint8_t touching = 0;
    float groundFriction = 10, airFriction = 0;
    float height = 50.0f, width = 50.0f;
};

struct Sprite
{
    std::string sprite = "Box";
    float width = 50.0f, height = 50.0f;
    SDL_Color color{255, 0, 0, 255};
};