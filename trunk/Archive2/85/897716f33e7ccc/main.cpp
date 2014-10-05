#include <iostream>
#include <string>
#include <vector>

template <int I = 10> struct C { void m(); };

template <int I> void C<I>::m() {
    std::cout << I << '\n';
}

int main()
{
    C<42> c;
    c.m();
}
