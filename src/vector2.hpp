#pragma once

template <typename T>
class Vector2 {
    T m_x;
    T m_y;
    
public:
    Vector2() {}
    Vector2(T x, T y) : m_x(x), m_y(y) {}
    ~Vector2() {}
    
    const T &x() { return m_x; }
    T &x() { return m_x; }
    
    const T &y() { return m_y; }
    T &y() { return m_y; }
    
    static SDL_FPoint toFPoint() { return {m_x, m_y}; }
}
