#include "Player.h"
#include "graphics/Graphics.h"
#include "movement/Movement.h"

Player::Player()
{
    movement = new Movement();
}

void Player::render()
{
    if (movement)
        Gfx::drawRect(movement->pos.x, movement->pos.y, 50.0f, 50.0f, SDL_Color{255, 0, 0, 255});
}

void Player::update(double dt)
{
    movement->update(dt);
}
