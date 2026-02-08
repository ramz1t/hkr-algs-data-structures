#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
public:
  using clock = std::chrono::high_resolution_clock;

  void begin();
  void stop();
  double time_ms() const;
  double time_ns() const;

private:
  clock::time_point start;
  clock::time_point end;
};

#endif