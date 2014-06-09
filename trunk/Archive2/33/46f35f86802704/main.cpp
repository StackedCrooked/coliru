#include <iostream>
#include <typeinfo>

#define $ (Money)

struct Money {
    Money(int i) : dollars(i) {}
    int dollars;
};

std::ostream &operator<<(std::ostream &os, Money m) {
    os << "$" << m.dollars;
    return os;
}

Money operator+(Money lhs, Money rhs) {
    return lhs.dollars + rhs.dollars;
}

int main() {
    std::cout << $ 32 + $ 64;
}