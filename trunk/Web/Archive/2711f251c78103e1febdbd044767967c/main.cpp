#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>

class Stopwatch {
public:
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point start;
    Stopwatch(): start(Clock::now()) {}
    void elapsed() {
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now()-start).count() << " ms\n";
    }
};

int main() {
    Stopwatch k;
    std::string str = "0123456789";
    for(size_t i = 1; i < 1000000; ++i) {
        std::next_permutation(str.begin(),str.end());
    }
    std::cout << str << '\n';
    k.elapsed();
}