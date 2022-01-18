#pragma once

#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>

#include "transformable.hpp"

class Sprite : public Transformable {
    // std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;

  public:
    Sprite() : m_texture(nullptr, SDL_DestroyTexture) {}

    bool loadFromFile(SDL_Renderer *renderer, std::string file) {
        // m_surface.reset(IMG_Load(f));
        m_texture.reset(IMG_LoadTexture(renderer, file.c_str()));

        if (m_texture.get() == nullptr) {
            std::cout << "File could not load! SDL Error: " << SDL_GetError() << "\n";
            return 0;
        } else {
            // m_texture.reset(SDL_CreateTextureFromSurface(m_surface.get()));
            SDL_QueryTexture(m_texture.get(), NULL, NULL, &size.x, &size.y);
            return 1;
        }
    }

    void draw(SDL_Renderer *renderer) {
        if (m_texture.get() != nullptr) {
            if (renderer != nullptr) {
                SDL_Rect srcrect = {
                    0,
                    0,
                    size.x,
                    size.y,
                };

                SDL_FRect dstrect = {
                    position.x - center.x * scale.x,
                    position.y - center.y * scale.y,
                    size.x * scale.x,
                    size.y * scale.y,
                };

                if (SDL_RenderCopyExF(renderer, m_texture.get(), &srcrect, &dstrect, angle, &center, SDL_FLIP_NONE) < 0) {
                    std::cout << "Sprite could not draw! SDL Error: " << SDL_GetError() << "\n";
                }
            } else {
                std::cout << "Sprite could not draw! renderer is nullptr!"
                          << "\n";
            }
        } else {
            std::cout << "Sprite could not draw! m_texture is nullptr!"
                      << "\n";
        }
    }
};
