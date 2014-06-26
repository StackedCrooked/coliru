#include <iostream>

auto makeLambda(double ratio) { return [=](double value) {return value * ratio;}; }

int main() {
    auto foo = makeLambda(2);
    std::cout << foo(3);
}