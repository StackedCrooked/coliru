#include <iostream>
#include <functional>


std::function<void(void)> a = [](){ std::function<void(void)> b = []() { std::cout << " ";};
    std::function<void(void)> c = []() { std::cout << "Hey bor";};c();b();std::cout << "mad?" << std::endl;};

int main() {
    a();
}