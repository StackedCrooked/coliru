#include <wheels/stopwatch.h++>
#include <wheels/chrono.h++>

#include <thread>
#include <chrono>
#include <iostream>

void f() {
    using namespace wheels::literal::chrono;
    std::this_thread::sleep_for(500_ms);
}

int main() {
    std::cout << "Sleeping for 500 milliseconds took " << wheels::to_milliseconds(wheels::time_execution(f)) << " milliseconds.";
}
