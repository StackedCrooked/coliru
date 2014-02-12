#include <iostream>

struct letter
{
    virtual ~letter() = default ;
    virtual void foo() const = 0 ;
    virtual void bar() const = 0 ;
};

template < char TAG > struct canned_impl : letter
{
    virtual void foo() const override { std::cout << TAG << "::foo " ; }
    virtual void bar() const override { std::cout << TAG << "::bar " ; }
};

struct A : canned_impl<'A'> {} ;
struct B : canned_impl<'B'> {} ;
struct C : canned_impl<'C'> {} ;
struct D : canned_impl<'D'> {} ;

struct add_things
{
    static void the_fun( letter& x, letter& y ) // reference to base class
    { std::cout << "add_things::the_fun: " ; x.foo() ; y.bar() ; std::cout << '\n' ; }
};

int main()
{
    A a ; B b ; C c ; D d ;
    letter* seq[] = { &a, &b, &c, &d } ;

    for( letter* px : seq ) for( letter* py : seq ) add_things::the_fun( *px, *py ) ;
}
