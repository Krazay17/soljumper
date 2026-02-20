#pragma once
#include "math/Vec2.h"
#include <SDL3/SDL.h>
#include <iostream>

enum ComponentBit
{
    POSITION = 1 << 0,
    VELOCITY = 1 << 1,
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

namespace Comp
{
    struct Position
    {
        float x, y;
    };

    struct LocalUser
    {
    };

    struct User
    {
        int playerNumber = 0;
        std::string name = "Player";
    };

    struct Input
    {
        int wishDirX = 0;
        bool jumpRequested = false;
        bool inventory = false;
    };

    struct Velocity
    {
        float vx, vy;
        float wishdir;
        float speed = 3;
        float airAccel = 3;
        float groundAccel = 9;
    };

    struct Body
    {
        BodyShape shape = BodyShape::BOX;
        BodyType type = BodyType::STATIC;
        uint8_t touching = 0;
        float mass = 100;
        float groundFriction = 10, airFriction = 0;
        float height = 50.0f, width = 50.0f;
    };

    struct Sprite
    {
        std::string sprite = "Box";
        float width = 50.0f, height = 50.0f;
        SDL_Color color{255, 0, 0, 255};
    };

    struct Inventory
    {
        int speedUp = 1;
        int speedDown = -1;
    };

    struct GamePoint
    {
        int score = 0;
        bool win = false;
    };
};