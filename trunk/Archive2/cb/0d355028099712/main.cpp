#include <cmath>

struct Foo
{
    operator double() const { return( 101.0 ); } // Implicit conversion to double
};

int main( int, char** )
{
    Foo foo;

    std::exp( foo );      // Compiles
    std::isfinite( foo ); // Does not

    return( 0 );
}