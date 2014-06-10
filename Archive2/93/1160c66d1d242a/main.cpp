#include <iostream>
#include <mutex>

template<typename Lock, typename Guard = std::lock_guard<Lock>, typename Func>
auto with(Lock& lock, Func func) {
    Guard guard(lock);
    return func();
}

std::mutex lock{};
int data{};

int main() {
    with(lock, [] {
        data = 42;
    });
    with(lock, [] {
        std::cout << data << std::endl;
    });
}