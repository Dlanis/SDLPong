#pragma once

#include <thread>
#include <cmath>
#include <SDL.h>

#include "ball.hpp"
#include "paddle.hpp"

constexpr float pi = 3.14159;

inline void sleep(double seconds) {
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}

inline constexpr bool intersects(float cx, float cy, float radius, float left, float top, float right, float bottom)
{
   float closestX = (cx < left ? left : (cx > right ? right : cx));
   float closestY = (cy < top ? top : (cy > bottom ? bottom : cy));
   float dx = closestX - cx;
   float dy = closestY - cy;

   return ( dx * dx + dy * dy ) <= radius * radius;
}

inline constexpr bool intersects(const Ball &ball, const Paddle &paddle) {
    SDL_FRect paddlerect = paddle.getRect();
    
    return intersects(ball.position.x, ball.position.y, ball.radius,
                      paddlerect.x, paddlerect.y, paddlerect.x + paddlerect.w, paddlerect.y + paddlerect.h);
}

inline constexpr SDL_FPoint rotate_vector(const SDL_FPoint &vector, const double &degree) {
    SDL_FPoint m_vector = vector;
    
    float l = (m_vector.x > 0 ? m_vector.x : 1) * (m_vector.y > 0 ? m_vector.y : 1);

    double angle = degree / (180 / pi);
    m_vector.x = l * std::cos(angle);
    m_vector.y = l * std::sin(angle);

    return m_vector;
}
