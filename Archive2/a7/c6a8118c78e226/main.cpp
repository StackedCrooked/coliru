#include <iostream>

auto f = [](auto i) { std::cout << i << std::endl; };

int main() {
    
    f(42);
    f("sometext");
}