#include <iostream>

int init( const char* var, int value )
{ std::cout << "initialise " << var << " with " << value << '\n' ; return value ; }

int assign( const char* var, int value )
{ std::cout << "assign " << value << " to " << var << '\n' ; return value ; }

struct A
{
    int a = init( "A::a", b + 66 ) ; // *** bad *** b is used before it is initialised
    int b = init( "A::b", 88 ) ;
    int c = init( "A::c", 10 ) ;

    A() // member initialisation in order of declaration ie. first a, then b, then c
    {
        std::cout << "in A::constructor body\n" ;
        a = assign( "A::a", b + 66 ) ; // fine
        b = assign( "A::b", 123 ) ;
        c = assign( "A::c", 0 ) ;
    }
};

int main ()
{
    A a ;
}
