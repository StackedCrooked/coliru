#include <chrono>
#include <future>
#include <thread>
#include <iostream>

void f() {
    std::cout << "a";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "b";
}

void g() {
    std::cout << "c";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "d";
}

int main() {
    std::async(std::launch::async, f), std::async(std::launch::async, g);
}
