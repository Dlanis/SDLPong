#pragma once

#include <SDL.h>

struct Transformable {
    SDL_FPoint position = {0, 0};
    SDL_FPoint center   = {0, 0};
    SDL_Point  size     = {0, 0};
    SDL_FPoint scale    = {1, 1};
    double angle = 0;
    
    SDL_FRect getRect() const {
        return {
                    position.x - center.x * scale.x,
                    position.y - center.y * scale.y,
                    size.x * scale.x,
                    size.y * scale.y,
                };
    }
};
