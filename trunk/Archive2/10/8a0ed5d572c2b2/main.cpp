#include <iostream>

struct Base {
    Base(int) {}
};

struct D1 : virtual Base {
    using Base::Base;
};

int main() {
    D1 d(4);
}