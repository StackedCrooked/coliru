#include <iostream>

int main() {
    int x = 0;
    int& r = x;
    std::cout << x << ' ' << r << '\n';
    x = 1;
    std::cout << x << ' ' << r << '\n';
    r = 2;
    std::cout << x << ' ' << r << '\n';
    return 0;
}
