#include <fstream>
#include <iostream>

struct X {};

std::ostream &operator<<(std::ostream &os, const X &) {
    return os << "abc";
}

int main() {
    X x;
    std::ofstream("out.txt") << x;
}