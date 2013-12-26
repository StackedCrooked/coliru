#include <cstdio>

struct A
{
    A& foo( char c ) { std::printf( "%c", c ) ; return *this ; }
    A& foo( int v ) { std::printf( "%d", v ) ; return *this ; }
    A& foo( double d ) { std::printf( "%.2f", d ) ; return *this ; }
    A& foo( const char* cstr ) { std::printf( "%s", cstr ) ; return *this ; }
};

int main()
{
    A cout ;

    A& r1 = cout.foo( "the values are: " ) ; // A::foo returns reference to cout
    A& r2 = r1.foo(55) ; // on the result r1 (reference to cout), call foo once again
    A& r3 = r2.foo( " and " ) ;
    A& r4 = r3.foo(34.56) ;
    r4.foo('\n') ;

    // use the references returned anonymously
    cout.foo( "the values are: " ).foo(55).foo( " and " ).foo(34.56).foo('\n') ;
}
