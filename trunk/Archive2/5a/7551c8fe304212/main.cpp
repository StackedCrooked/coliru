#include <iostream>

struct A
{
    A( int i ) : v(i) {}

    A( const A& that ) : v(that.v) { std::cout << "A::copy_constructor one \n" ; }

    A( A& that ) : v(that.v) { std::cout << "A::copy_constructor two\n" ; }

    A( A&& that ) noexcept : v(that.v) { std::cout << "A::move_constructor\n" ; }

    const int v ;
};

template < typename T > T build( T&& t ) // rvalue reference
{ return T( std::forward<T>(t) ) ; }

A foo() { A a(400) ; return a ; }

int main()
{
    A a1(100) ;
    const A a2(200) ;

    // forwarded as A&
    A a3 = build(a1) ; // A::copy_constructor two
    std::cout << a3.v << '\n' ;

    // forwarded as const A&
    A a4 = build(a2) ; // A::copy_constructor one
    std::cout << a4.v << '\n' ;

    // forwarded as A&&
    A a5 = build( A(300) ) ; // A::move_constructor
    std::cout << a5.v << '\n' ;

    // forwarded as A&&
    A a6 = build( foo() ) ; // A::move_constructor
    std::cout << a6.v << '\n' ;
}
