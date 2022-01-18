#pragma once

#include <chrono>

class Clock {
    using clock_type = std::chrono::steady_clock;
    using point_type = std::chrono::steady_clock::time_point;
    using duration_type = std::chrono::duration<double>;

  public:
    Clock() {}
    ~Clock() {}

    double elapsed() {
        now = clock_type::now();
        return std::chrono::duration_cast<duration_type>(now - last).count();
    }
    
    double restart() {
        auto time = elapsed();
        last = clock_type::now();
        return time;
    }

  private:
    point_type now;
    point_type last;
};
