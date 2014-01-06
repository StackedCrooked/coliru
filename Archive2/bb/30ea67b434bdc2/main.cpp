#include <iostream>

struct A
{
    int i;
    int j = 42;
    A(int foo) : i(foo) {}
    A() = default;
};

void non_array() {
}

int main() {
    {
        // non-array case
        A a{};
        std::cout << "non-array:" << a.i << ' ' << a.j << '\n';
    }
    {
        // array case
        A foo[3] = {A(13), {}};
        std::cout << "array (with {}): " << foo[1].i << ' ' << foo[1].j << '\n'
                  << "array (without): " << foo[2].i << ' ' << foo[2].j << '\n';
    }
}
