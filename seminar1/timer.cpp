#include "timer.hpp"

void Timer::begin() {
  start = clock::now();
}

void Timer::stop() {
  end = clock::now();
}

double Timer::time_ms() const {
  return std::chrono::duration<double, std::milli>(end - start).count();
}
double Timer::time_ns() const {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}