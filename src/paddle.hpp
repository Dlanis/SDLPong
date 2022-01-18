#pragma once

#include <iostream>
#include <SDL.h>

#include "sprite.hpp"
#include "entity.hpp"

class Paddle : public Sprite, public Entity {

public:
    Paddle() {}
    ~Paddle() {}
    
    float speed = 256;
};
