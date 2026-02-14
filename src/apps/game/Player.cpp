#include "Player.h"
#include "input/Input.h"
#include "graphics/Graphics.h"

void Player::move(double dt)
{
    applyGravity(gravity * dt);
    walk();
    pos += velocity;
}

void Player::walk()
{
    int direction = 0;
    if (Input::held(Actions::LEFT))
        direction -= 1;
    if (Input::held(Actions::RIGHT))
        direction += 1;

    velocity.x = direction * speed;
}

void Player::jump()
{
    if (Input::pressed(Actions::JUMP))
    {
        pos.y -= 1;
        velocity.y = -10;
    }
}

void Player::update(double dt)
{
    jump();
    move(dt);
}

void Player::applyGravity(float g)
{
    float floor = Gfx::height - height;
    if (pos.y < floor)
    {
        velocity.y += g;
    }
    else if (pos.y < 0)
    {
        pos.y = 0;
        velocity.y = 0;
    }
    else
    {
        pos.y = floor;
        velocity.y = 0;
    }
}

void Player::render()
{
    Gfx::drawRect(pos.x, pos.y, 50.0f, 50.0f, SDL_Color{255, 0, 0, 255});
}
