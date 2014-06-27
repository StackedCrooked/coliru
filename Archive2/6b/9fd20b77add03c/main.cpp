#include <iostream>

struct type {
    int x;
    type() : x(0) {}
};

int& operator&(type& t) {
    return t.x;
}

int main() {
    type a;
    (&a) = 1;
    std::cout << a.x;
}