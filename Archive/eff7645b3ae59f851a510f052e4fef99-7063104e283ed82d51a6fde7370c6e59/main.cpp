#include <thread>
#include <vector>
#include <iostream>

struct Counter {
    size_t n;
    Counter(): n(0) {}
    void increment() {
        ++n;
    }
    void decrement() {
        --n;
    }
};

int main() {
    Counter c;
    std::vector<std::thread> threads;
    for(size_t i = 0; i < 10; ++i) {
        threads.push_back(std::thread([&c]() {
            for(size_t j = 0; j < 1000; ++j)
                c.increment();
        }));
    }

    for(auto&& thread : threads)
        thread.join();
    std::cout << c.n; // This isn't supposed to print 10000
}

