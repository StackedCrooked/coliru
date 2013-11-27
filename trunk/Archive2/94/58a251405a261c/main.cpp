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
    vec.emplace_back(base);
    std::cout << '\n';
    vec.emplace_back(std::move(base));
}