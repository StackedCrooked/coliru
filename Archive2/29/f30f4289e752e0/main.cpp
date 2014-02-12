#include <iostream>

int main() {
    auto a = 0;
    auto b = &a;
    auto lol = &b;
    std::cout << **lol << '\n';
    return 0;
}
