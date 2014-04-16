#include <iostream>

void f();
namespace N {
    class X {
        static int i;
        friend void f() { std::cout << i << '\n'; }
    };
    int X::i = 1;
}



int main()
{
    N::f();
}