#include <iostream>
namespace A {
    class X {
        friend void f(X) { std::cout << "friend f(X)\n"; }
    };
}

int main()
{
    A::X x;
    f(x);
}