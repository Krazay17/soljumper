#pragma once

class Movement;
class Player
{
    Movement *movement;

public:
    Player();
    void render();
    void update(double dt);
};