#include <iostream>
#include <thread>

int main() {
    std::thread{[] {std::cout << "Thread\n";}}.join();
    std::cout << "Main\n";
}