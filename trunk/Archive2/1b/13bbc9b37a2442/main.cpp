#include <iostream>
#include <typeinfo>
struct A{ int i; };
struct B{ int i; void f(); };

int main()
{
    std::cout << typeid(A::i).name() << '\n';
    std::cout << typeid(B::i).name() << '\n';
    std::cout << typeid(B::f).name() << '\n';
}
