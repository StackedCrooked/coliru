#include <thread>
#include <chrono>
#include <iostream>

int main() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "...\n";
}