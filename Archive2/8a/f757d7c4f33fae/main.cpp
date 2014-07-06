#include <chrono>

using namespace std::chrono;

int main() {
  auto now = system_clock::now();
  time_point<system_clock> epoch;
  microseconds ms = duration_cast<milliseconds>(now - epoch);
  microseconds hs = std::chrono::hours(1);
  auto mm = ms % hs;
  mm.count();
}