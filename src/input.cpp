#include "input.hpp"

void gm::Input::prepare() {
    keys_jp.clear();
    keys_jr.clear();
    buttons_jp.clear();
    buttons_jr.clear();
}

void gm::Input::update(const SDL_Event &event) {
    if (!event.key.repeat) {
        switch (event.type) {
        case SDL_KEYDOWN:
            keys_p[event.key.keysym.sym] = 1;
            keys_jp[event.key.keysym.sym] = 1;
            break;

        case SDL_KEYUP:
            keys_p[event.key.keysym.sym] = 0;
            keys_jr[event.key.keysym.sym] = 1;
            break;

        case SDL_MOUSEBUTTONDOWN:
            buttons_p[event.button.button] = 1;
            buttons_jp[event.button.button] = 1;
            break;

        case SDL_MOUSEBUTTONUP:
            buttons_p[event.button.button] = 0;
            buttons_jr[event.button.button] = 1;
            break;

        case SDL_MOUSEMOTION:
            mouse_pos = {
                event.motion.x,
                event.motion.y,
            };
            break;

        default:
            break;
        }
    }
}

bool gm::Input::isKeyPressed(int code) { return keys_p[code]; }
bool gm::Input::isKeyJustPressed(int code) { return keys_jp[code]; }
bool gm::Input::isKeyJustReleased(int code) { return keys_jr[code]; }

bool gm::Input::isButtonPressed(int code) { return buttons_p[code]; }
bool gm::Input::isButtonJustPressed(int code) { return buttons_jp[code]; }
bool gm::Input::isButtonJustReleased(int code) { return buttons_jr[code]; }
const SDL_Point &gm::Input::getMousePosition() { return mouse_pos; }