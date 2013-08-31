#include <chrono>
#include <iostream>

class stopwatch {
public:
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start;
    stopwatch(): start(Clock::now()) {}
    void elapsed() {
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms\n";
    }
    void reset() {
        start = Clock::now();
    }
};