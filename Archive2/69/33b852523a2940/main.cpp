#include <iostream>

template<typename T = double>
T pi = 3.14159265358979323846264338327950;

int main() {
    auto foo = [](auto i) {return i;};
    std::cout << pi<> << '\n';
}