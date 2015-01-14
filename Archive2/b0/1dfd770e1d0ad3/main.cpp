#include <iostream>


struct A
{
    int n;
};


struct B
{
    B() {}
    int n;
};


struct C
{
    C() = default;
    C(int n) : n(n) {}
    int n;
};



int main()
{
    int a = 1, b = 1, c = 1;
    new (&a) A();
    new (&b) B();
    new (&c) C();
    std::cout << a << b << c << std::endl;
}
