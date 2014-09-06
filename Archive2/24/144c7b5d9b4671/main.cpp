#include <thread>
#include <chrono>
#include <iostream>
#include <future>

void start() {
    std::cout << "starting..!!\n";
}

void stop() {
    std::cout << "ending..!!\n";
}

template<typename Duration>
void stopper(const Duration& d) {
    std::this_thread::sleep_for(d);
    stop();
}

template<typename Duration>
auto start_for(const Duration& d) -> decltype(std::async(std::launch::async, stopper<Duration>, d)) {
    start();
    return std::async(std::launch::async, stopper<Duration>, d);
}

int main() {
    // how can I do this without storing the future object?
    auto&& _ = start_for(std::chrono::seconds(1));
    for(unsigned i = 0; i < 10; ++i) {
        std::cout << i << '\n';
    }
}
