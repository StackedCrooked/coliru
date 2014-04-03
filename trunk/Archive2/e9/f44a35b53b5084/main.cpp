#include <iostream>
#include <thread>

int main() {
    int i = 0;
//    std::thread{[](int &r) {r = 1;}, i}.join();
    std::thread{[](int &r) {r = 1;}, std::ref(i)}.join();
    std::cout << i;
}