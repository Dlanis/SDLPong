#pragma once

#include <iostream>
#include <memory>
#include <SDL.h>

class Window {
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    bool m_isopen;
    
public:
    Window() : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer), m_isopen(1) {}
    
    SDL_Window *window() {
        return m_window.get();
    }
    
    SDL_Renderer *renderer() {
        return m_renderer.get();
    }
    
    bool create(std::string title, const int w, const int h, Uint32 flags = SDL_WINDOW_SHOWN) {
        m_window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags));
        if (m_window.get() == nullptr) {
            std::cout << "Window could not created! SDL Error: " << SDL_GetError() << "\n";
            return 0;
        }
        
        m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
        if (m_renderer.get() == nullptr) {
            std::cout << "Renderer could not created! SDL Error: " << SDL_GetError() << "\n";
            return 0;
        }
        // SDL_RenderSetLogicalSize(m_renderer.get(), w, h);
        
        m_isopen = 1;
        return 1;
    }
    
    void close() {
//         m_renderer.reset(nullptr);
//         m_window.reset(nullptr);
        
        m_isopen = 0;
    }
    
    bool isOpen() const {
        return m_isopen;
    }
    
    void clear(SDL_Color color = {0, 0, 0, 255}) {
        SDL_SetRenderDrawColor(m_renderer.get(), color.r, color.g, color.b, color.a);
        SDL_RenderClear(m_renderer.get());
    }
    
    void present() {
        SDL_RenderPresent(m_renderer.get());
    }
    
    bool pollEvent(SDL_Event &event) {
        return SDL_PollEvent(&event);
    }
};
