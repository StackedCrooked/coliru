#include <iostream>

namespace N {
    void f();
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