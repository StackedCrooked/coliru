#include <future>
#include <thread>
#include <chrono>
#include <iostream>

int lazy_add(int x, int y) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "done adding\n";
    return x + y;
}

std::future<int> async_add(int x, int y) {
    return std::async(std::launch::async, lazy_add, x, y);
}

int main() {
    auto&& x = async_add(10, 11);
    std::cout << "...\n";
    std::cout << ".....\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Slept\n";
    std::cout << x.get() << '\n';
}