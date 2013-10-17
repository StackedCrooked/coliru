#include <iostream>
#include <functional>

void test() {
    std::cout << "Test";
}

int main() {
    std::function<void()> x = test;
    x();
}