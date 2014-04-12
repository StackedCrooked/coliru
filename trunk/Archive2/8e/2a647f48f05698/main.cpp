#include <iostream>

namespace A {
    int i = 2;
    namespace N {
        int i = 1;    
        void f();
    }
}


int i = 3;
void A::N::f() {
    std::cout << i << '\n';;
    // The following scopes are searched for a declaration of i:
    // 1) outermost block scope of A::N::f, before the use of i
    // 2) scope of namespace N
    // 3) scope of namespace A
    // 4) global scope, before the definition of A::N::f
}

int main()
{
    A::N::f();
}