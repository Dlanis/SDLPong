#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <unordered_map>
#include <SDL.h>

namespace gm {

class Input {
  public:
    static void prepare();
    static void update(const SDL_Event &event);

    static bool isKeyPressed(int code);
    static bool isKeyJustPressed(int code);
    static bool isKeyJustReleased(int code);

    static bool isButtonPressed(int code);
    static bool isButtonJustPressed(int code);
    static bool isButtonJustReleased(int code);
    static const SDL_Point &getMousePosition();

  private:
    inline static std::unordered_map<int, bool> keys_p;
    inline static std::unordered_map<int, bool> keys_jp;
    inline static std::unordered_map<int, bool> keys_jr;

    inline static std::unordered_map<int, bool> buttons_p;
    inline static std::unordered_map<int, bool> buttons_jp;
    inline static std::unordered_map<int, bool> buttons_jr;

    inline static SDL_Point mouse_pos;
};

} // namespace gm
#endif // INPUT_H