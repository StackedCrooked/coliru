#include <wheels/stopwatch.h++>
#include <wheels/chrono.h++>

#include <thread>
#include <chrono>

int f() {
    using wheels::literals::duration;
    std::this_thread::sleep_for(500_ms);
}

int main() {
    std::cout << wheels::to_milliseconds(wheels::time_execution(f)) << " milliseconds.";
}
