// http://stackoverflow.com/questions/25114597/how-to-print-int128-in-g
// g++ Undefined behavior (ambiguous overload for operator<<)
// clang++ compiles fine
#include <iostream>
using std::ostream;
using TYPE = __int128;

ostream & operator<<( ostream & o, TYPE x ) { return o; }

namespace N {
    template<typename T>
    struct A {
        T x{0};
        friend ostream & operator<<( ostream & o, A s ) { return o; }
    };

    struct B {
        B( ostream & o ) {
            A<TYPE> y;
            o << y.x;
        }
        A<int> z;
    };
}

int main() {}