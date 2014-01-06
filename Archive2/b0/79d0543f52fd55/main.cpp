#include <iostream>
#include <functional>

int function_one( int a, int b )
{
    const int result = a*a + b*b ;
    std::cout << "function_one( " << a << ", " << b << " ) => " << result << '\n' ;
    return result ;
}

double function_two( double a, double b, double c )
{
    const double result = a + b - c ;
    std::cout << "function_two( " << a << ", " << b << ", " << c << " ) => " << result << '\n' ;
    return result ;
}

int main()
{
    int x = 10 ;
    int y = 5 ;
    function_one( x, y ) ; // function_one( 10, 5 ) => 125

    // f1 is a callable object that can be called with no arguments
    // f1() would call function_one(10,5)
    const auto f1 = std::bind( function_one, 10, 5 ) ;
    f1() ; // function_one( 10, 5 ) => 125

    // f2() would call function_one(3,8)
    const auto f2 = std::bind( function_one, 3, 8 ) ;
    f2() ; // function_one( 3, 8 ) => 73

    // f3() would call function_two( 3.1, 28, 5.2 )
    const auto f3 = std::bind( function_two, 3.1, 28, 5.2 ) ;
    f3() ; // function_two( 3.1, 28, 5.2 ) => 25.9
}
