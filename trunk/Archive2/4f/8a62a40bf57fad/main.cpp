#include <iostream>

struct A
{
    A( int i = 0 ) : v(i) { std::cout << "initialisation\n" ; }
    A( const A& that ) : v(that.v) { std::cout << "copy initialisation\n" ; }
    A& operator= ( const A& that ) = delete ;
    int v ;
};

void foo( A ) {}

int main()
{
    A a = 1234 ; // initialisation
    
    foo(a) ; // copy initialisation

    foo(5678) ; // initialisation
    
    #ifdef TRY_ASSIGNMENT
    a = 5678 ; // *** error *** can't assign to a, assignment is explicitly deleted
    #endif // TRY_ASSIGNMENT
}
