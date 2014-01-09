#include <iostream>

auto foo = [](const auto a) {
    return a;
};

int main() {
    std::cout << foo(3.4);
}