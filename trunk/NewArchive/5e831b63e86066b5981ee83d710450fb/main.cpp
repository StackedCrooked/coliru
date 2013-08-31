#include <wheels/stopwatch.h++>
#include <wheels/chrono.h++>

#include <thread>
#include <chrono>
#include <iostream>

void take_a_nap() {
    using namespace wheels::literal::chrono;
    std::this_thread::sleep_for(500_ms);
}

int main() {
    std::cout << "Taking a nap took " << wheels::to_milliseconds(wheels::time_execution(take_a_nap)) << " milliseconds.";
}
