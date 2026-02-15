#include "Player.h"
#include "graphics/Graphics.h"
#include "movement/Movement.h"

Player::Player()
{
    movement = new Movement(0, 0, height, width);
}

void Player::render(double dt, double alpha)
{
    if (movement)
    {
        pos.x = lerp_linear(pos.x, movement->pos.x, alpha);
        pos.y = lerp_linear(pos.y, movement->pos.y, alpha);
    }
    Gfx::drawRect(pos.x, pos.y, 50.0f, 50.0f, SDL_Color{255, 0, 0, 255});
}

void Player::update(double dt)
{
    movement->update(dt);
}
