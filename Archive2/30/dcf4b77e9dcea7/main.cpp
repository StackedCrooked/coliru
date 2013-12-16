#include <iostream>
#include <vector>

class x {
public:
    x() { std::cout << "Ctor\n"; }
    x(const x&) { std::cout << "Copy ctor\n"; }
    x(x&&) { std::cout << "Move\n"; }
};

int main() {
    std::vector<x> vec;
    x base;
    vec.emplace_back(std::move(base));
}