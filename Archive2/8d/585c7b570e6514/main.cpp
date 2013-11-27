#include <iostream>
#include <vector>

class x {
public:
    x() {}
    x(const x&) { std::cout << "Copy ctor\n"; }
    x(x&&) noexcept { std::cout << "Move\n"; }
};

int main() {
    x base;
    std::vector<x> vec;
    std::cout << "Capacity 1: " << vec.capacity() << std::endl;
    
    vec.emplace_back(base);
    std::cout << "Capacity 2: " << vec.capacity() << std::endl;
    
    std::cout << '\n';
    vec.emplace_back(std::move(base));
    std::cout << "Capacity 3: " << vec.capacity() << std::endl;
}