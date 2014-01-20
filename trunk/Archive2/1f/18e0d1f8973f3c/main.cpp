#include <iostream>

struct A
{
    A() { std::cout << "(A::A)"; }
};

struct B
{
    B() { std::cout << "(B::B)"; }
};

struct C
{
    template<typename ...Args>
    C(Args && ...) {}
};

int main(int agrc, char *argv[])
{
    C {A(), B()}; // <-- prints (B::B)(A::A)
    std::cout << std::endl;
    C {(A(), B())}; // <-- prints (A::A)(B::B)
    std::cout << std::endl;

    return 0;
}