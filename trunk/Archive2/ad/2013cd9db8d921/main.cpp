#include <iostream>

struct A {
    int i;
    A():i(1){}
    operator int&() { return i; }
};

void f(int j) { std::cout << j << '\n'; }

int& rri = A();

int main()
{
    int& ri = A();
    f(ri);
    f(rri);
    std::cout << ri << '\n';
    std::cout << rri << '\n';
}