#include <iostream>

int main() {
    int x = 0;
    int* p = &x;
    std::cout << x << ' ' << *p << '\n';
    p = nullptr;
    std::cout << x << ' ' << *p << '\n';
    return 0;
}
