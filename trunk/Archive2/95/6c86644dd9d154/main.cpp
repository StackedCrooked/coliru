#include <stdio.h>
#include <string>

typedef int f;
namespace N {
    struct A {
        friend void f(A &);
        operator int();
        void g(A a) {
            int i = f(a);
        }
    };
}

int main() {
}