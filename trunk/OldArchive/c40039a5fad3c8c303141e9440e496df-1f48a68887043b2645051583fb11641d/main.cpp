#include <chrono>
#include <thread>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;

class stopwatch {
public:
    Clock::time_point start;
    stopwatch(): start(Clock::now()) {}
    void elapsed() {
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms\n";
    }
    void reset() {
        start = Clock::now();
    }
};

void func() {
    std::cout << "....\n";
    std::chrono::seconds duration(1);
    std::this_thread::sleep_for(duration);
}

int main(){
    stopwatch stop;
    func();
    stop.elapsed();
}

