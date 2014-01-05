#include <iostream>

struct A
{
    int i;
    A(int j) : i{j} {};
    A() = default;
};

int main() {
    A a[3] = { A(1) };
    std::cout << a[1].i << ' ' << a[2].i << '\n';
}