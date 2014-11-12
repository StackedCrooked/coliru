#include <iostream>

int main() {
    int x = 0;
    int* p = &x;
    std::cout << x << ' ' << *p << std::endl;
    p = nullptr;
    std::cout << x << ' ' << *p << std::endl;
    return 0;
}
