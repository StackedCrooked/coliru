#include <iostream>

typedef int f;
namespace N {
    struct A {
        friend void f(A &);
        operator int();
        void g(A a) {
            int i = f(a);   // f is the typedef, not the friend
                            // function: equivalent to int(a)
        }
    };
}