#pragma once

#include <iostream>
#include <memory>
#include <SDL.h>

#include "sprite.hpp"
#include "entity.hpp"

class Ball : public Sprite, public Entity {
  public:
    float radius;
    float speed = 384;
    double rotation = 0;

    Ball() : radius(24.f) {}
};
