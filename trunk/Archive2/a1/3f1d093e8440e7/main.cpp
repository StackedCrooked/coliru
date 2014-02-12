#include <iostream>

struct f {
    f(int) { std::cout << "f\n"; }
    f(const f&) { std::cout << "g\n"; }
    f& operator=(const f&) { std::cout << "h\n"; return *this; }
};

int main() {
    f x = 10;
    f y(10);
    x = y;
}