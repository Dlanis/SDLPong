#pragma once

#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

#include "transformable.hpp"

class Text : public Transformable {
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> m_font;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;
    std::string m_string;
    bool m_changed;
    SDL_Color m_color;

  public:
    Text() : m_font(nullptr, TTF_CloseFont), m_texture(nullptr, SDL_DestroyTexture), m_changed(1), m_color({255, 255, 255, 255}) {}
    ~Text() {}

    void loadFont(std::string file, int size) {
        m_font.reset(TTF_OpenFont(file.c_str(), size));
        if (m_font == nullptr) {
            std::cout << "File could not load! SDL Error: " << SDL_GetError() << "\n";
        } else {
            m_changed = 1;
        }
    }

    void setFontSize(int size) {
        TTF_SetFontSize(m_font.get(), size);
        m_changed = 1;
    }

    void setString(std::string string) {
        if (m_string != string) {
            m_string = string;
            m_changed = 1;
        }
    }
    const std::string &getString() { return m_string; }

    void draw(SDL_Renderer *renderer) {
        if (renderer != nullptr) {
            if (m_font.get() != nullptr) {
                if (m_string != "") {
                    if (m_changed) {
                        SDL_Surface *surface = TTF_RenderText_Blended(m_font.get(), m_string.c_str(), m_color);
                        m_texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
                        SDL_FreeSurface(surface);

                        if (m_texture != nullptr) {
                            SDL_QueryTexture(m_texture.get(), NULL, NULL, &size.x, &size.y);
                            m_changed = 0;
                        } else {
                            std::cout << "Text texture could not draw! SDL Error: " << SDL_GetError() << "\n";
                        }
                    }
                }
            } else {
                std::cout << "Text texture could not draw! m_font is nullptr!"
                          << "\n";
            }
            if (m_texture.get() != nullptr) {
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
                if (m_string != "") {
                    std::cout << "Text could not draw! m_texture is nullptr!"
                              << "\n";
                }
            }
        } else {
            std::cout << "Text could not draw! renderer is nullptr!"
                      << "\n";
        }
    }
};