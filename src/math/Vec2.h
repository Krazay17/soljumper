#pragma once
#include <cmath>

class Vec2
{
public:
    float x, y;

    // Constructors
    inline Vec2() : x(0.0f), y(0.0f) {}
    inline Vec2(float x_val, float y_val) : x(x_val), y(y_val) {}

    inline Vec2 set(float vx, float vy)
    {
        x = vx;
        y = vy;
        return *this;
    }

    // Example operation: vector addition
    inline Vec2 operator+(const Vec2 &other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    // Example operation: scalar multiplication
    inline Vec2 operator*(float scalar) const
    {
        return Vec2(x * scalar, y * scalar);
    }

    // Example operation: calculating magnitude (length)
    inline float magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    inline Vec2 lerp(const Vec2 &other, const float alpha) const
    {
        return Vec2(x + (other.x - x) * alpha, y + (other.y - y) * alpha);
    }

    inline Vec2 lerp_fixed(const Vec2 &target, float speed, float dt) const
    {
        float alpha = 1.0f - std::exp(-speed * dt);
        return lerp(target, alpha);
    }
};
