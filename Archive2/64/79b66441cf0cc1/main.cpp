#include <iostream>

struct letter
{
    virtual ~letter() = default ;
    virtual void foo() const = 0 ;
    virtual void bar() const = 0 ;
};

struct A : letter
{
    virtual void foo() const override { std::cout << "A::foo " ; }
    virtual void bar() const override { std::cout << "A::bar " ; }
};

struct B : letter
{
    virtual void foo() const override { std::cout << "B::foo " ; }
    virtual void bar() const override { std::cout << "B::bar " ; }
};

struct C : letter
{
    virtual void foo() const override { std::cout << "C::foo " ; }
    virtual void bar() const override { std::cout << "C::bar " ; }
};

struct add
{
    static void funr( letter& x, letter& y ) // reference to base class
    { std::cout << "add::funr: " ; x.foo() ; y.bar() ; std::cout << '\n' ; }

    static void funp( letter* px, letter* py ) // pointer to base class
    { std::cout << "add::funp: " ; if( px && py ) funr( *px, *py ) ; }
};

int main()
{
    A a ;
    B b ;
    C c ;

    letter* seq[] = { &a, &b, &c } ;

    for( letter* px : seq )
        for( letter* py : seq ) { add::funp(px,py) ; add::funr( *px, *py ) ; }
}
