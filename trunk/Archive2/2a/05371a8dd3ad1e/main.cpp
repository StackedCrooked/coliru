#include <iostream>

struct A { A(int) {} };

void foo( A ) { std::cout << "Foo(A)\n" ; }

void foo( long double ) { std::cout << "Foo(long double)\n" ; }

int main( int argc, char* [] )
{
    foo( argc ) ; // overload resolves to Foo(long double)
                  // even though int => long double (standard conversion)
                  // is more expensive than int => A (user-defined conversionb)
}
