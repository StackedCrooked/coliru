#include <iostream>

struct A {
    int i;
    A():i(1){}
    operator int&() { return i; }
};

int& rri = A();

int main()
{
    int& ri = A();
    std::cout << ri << '\n';
    std::cout << rri << '\n';
}