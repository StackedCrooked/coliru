#include <iostream>

typedef int f;
namespace N{
    struct A{
        void f(int);
        f a = 11;
    };
}

int main()
{
    N::A a;
    std::cout << a.a << '\n';
}