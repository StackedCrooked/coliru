#include <iostream>
#include <functional>
#include <utility>
#include <vector>

struct A
{
    using callback_type = std::function< void() > ;

    template < typename FN, typename... ARGS > void register_callback( FN&& fn, ARGS&&... args )
    { callbacks.emplace_back( std::bind( std::forward<FN>(fn), std::forward<ARGS>(args)... ) ) ; }

    void do_callback() const { for( auto& fn : callbacks ) fn() ; }

    std::vector<callback_type> callbacks ;
};

int foo( int a, int b ) { std::cout << "::foo(" << a << ',' << b << ")\n" ; return a+b ; }

struct bar { void operator() ( double& d ) const { std::cout << "bar::operator()(" << d << ")\n" ; d += 1 ; } };

int main()
{
    const auto closure = []( int a, double d ) { std::cout << "main::closure(" << a << ',' << d << ")\n" ; return a+d ; };

    struct B { int v = 7 ; void mem_fun( int x ) { std::cout << "B::memfun(" << this << ',' << x << ")\n" ; v *= 9 ; } };

    A a ;
    B b ;
    double d = 9.9 ;
    a.register_callback( foo, 12, 34 ) ;
    a.register_callback( bar(), std::ref(d) ) ;
    a.register_callback( closure, 12, 3.4 ) ;
    a.register_callback( &B::mem_fun, std::ref(b), 56 ) ;

    a.do_callback() ;
    
    std::cout << d << ' ' << b.v << '\n' ;
}
