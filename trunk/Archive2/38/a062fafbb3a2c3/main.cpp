#include <iostream>

struct foo {};

std::ostream &operator<<(std::ostream& o, foo f) {
    o << "hi";
    return o;
}

int main() {
    std::cout << foo();
}