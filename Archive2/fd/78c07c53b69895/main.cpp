#include <iostream>
#include <functional>

template < typename T > struct base
{
    // http://en.cppreference.com/w/cpp/utility/functional/function
    void call_it( std::function< void(int) > fn )
    {
        std::cout << "base::call_it => " ;
        fn(100) ;
    }
};

struct derived : base<int>
{
    void foo( int ) { std::cout << "derived::foo\n" ; }
    void bar( int ) { std::cout << "derived::bar\n" ; }

    // http://en.cppreference.com/w/cpp/utility/functional/bind
    void call_foo() { call_it( std::bind( &derived::foo, this, std::placeholders::_1 ) ) ; }
    void call_bar() { call_it( std::bind( &derived::bar, this, std::placeholders::_1 ) ) ; }
};


int main()
{
    derived d ;
    d.call_foo() ;
    d.call_bar() ;
    d.call_it( []( int ) { std::cout << "call this\n"; } ) ;
}
