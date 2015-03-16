#include <utility>
#include <cstddef>
#include <iostream>

int main() {
    short x=1, y=2;
    static_assert( std::is_same<int, decltype(x-y)>{}, "subtracting two shorts gets an `int`, not a `short`" );
    int a=3,b=4;
    // if you use {} style initialization, it is an error to have a narrowing conversion:
    //short z1 = {b-a};
    // but not if you don't use {}:
    short z2 = b-a;
    (void)x;(void)y;(void)a;(void)b;(void)z2; // block unused var warnings.
}