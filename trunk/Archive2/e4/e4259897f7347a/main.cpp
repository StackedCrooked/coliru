#include <iostream>
#include <cmath>

struct A
{
    // *** warning *** the value of A::second is used before it is initialized
    // initialization of non-static members are in order of declaration
    // A::first will be initialized before A::second
    // behaviour of this constructor changes if we change the order of declaration
    A( int a ) : second( 4.3*a*a - 2.6*a + 3.5 ), first( std::sqrt(second) ) {}

    A( long a )
    {
        // assignments take place in the order that we specify
        // A::second is assigned to, and then, A::first will be assigned to
        // behaviour of this constructor does not change if we change the order of declaration
        second = 4.3*a*a - 2.6*a + 3.5 ;
        first = std::sqrt(second) ;
    }

    double first ;
    double second ;
};

int main()
{
    A a1( 23 ) ;
    std::cout << a1.first << ' ' << std::sqrt(a1.second) << '\n' ;

    A a2( 23L ) ;
    std::cout << a2.first << ' ' << std::sqrt(a2.second) << '\n' ;
}
