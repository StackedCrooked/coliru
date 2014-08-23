#include <cstdio>
#include <utility>
#include <iostream>

struct base
{
    base() = default ;
    base( base&& ) noexcept { std::puts( "base::move_constructor" ) ; }
    virtual ~base() = default ;
    virtual const char* id() const { return "base" ; }
};

struct derived : base
{
    derived() = default ;
    derived( derived&& ) noexcept { std::puts( "derived::move_constructor" ) ; }
    virtual const char* id() const override { return "derived" ; }
};

struct A
{
    derived d ;

    // prvalue: not polymorphic
    base foo_prvalue_base() { return std::move(d) ; } // sliced and move constructed prvalue
    derived foo_prvalue_derived() { return std::move(d) ; } // move constructed prvalue

    // xvalue: polymorphic
    base&& bar_xvalue() { return std::move(d) ; } // xvalue
};

int main()
{
    A a ; 
    
    // moved, not polymorphic
    std::cout << "1.\n" ;
    std::cout << a.foo_prvalue_base().id() << '\n' ;
    
    // moved, not polymorphic
    std::cout << "\n2.\n" ;
    std::cout << a.foo_prvalue_derived().id() << '\n' ;
    
    // moveable xvalue, polymorphic, but not moved
    std::cout << "\n3.\n" ;
    std::cout << a.bar_xvalue().id() << '\n' ;

    // moveable xvalue, polymorphic, sliced and moved
    std::cout << "\n4.\n" ;
    auto x = a.bar_xvalue() ;

    // moveable xvalue, polymorphic, type restored and moved
    std::cout << "\n5.\n" ;
    auto y = dynamic_cast<derived&&>( a.bar_xvalue() ) ;
}
