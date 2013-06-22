#include <iostream>
#include <exception>
#include <stdexcept>
#include <functional>

typedef void(*foo)(int);

int main() {
    std::cout <<sizeof(std::function<void(int)>) << '\n';
    std::cout <<sizeof(foo) << '\n';
}