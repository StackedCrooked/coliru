#include <iostream>
#include <vector>

class x {
public:
    x() noexcept {}
    x(const x&) noexcept { std::cout << "Copy ctor\n"; }
    x(x&&) noexcept { std::cout << "Move\n"; }
};

int main() {
    x base;
    std::vector<x> vec;
    vec.reserve(2);
    vec.emplace_back(base);
    vec.emplace_back(std::move(base));
}