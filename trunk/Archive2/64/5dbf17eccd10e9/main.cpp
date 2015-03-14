#include <iostream>

struct a {
    a() { std::cout << "a\n"; }
};

struct b : virtual a {
    b() : a() { std::cout << "b\n"; }
};

struct c : virtual b {
    c() : b() { std::cout << "c\n"; }
};

struct d : virtual a, virtual c {
    d() : a(), c() { std::cout << "d\n"; }
};

int main()
{
    d x;
    std::cout << "\n";
    c y;
}
