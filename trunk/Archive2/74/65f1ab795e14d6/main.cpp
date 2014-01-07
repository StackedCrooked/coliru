#include <iostream>

struct base
{
    virtual ~base() {} ;

    virtual void foo() const = 0 ; // pure
};

struct derived : base
{
    virtual void foo() const override { std::cout << "derived::foo\n" ; }
};

struct also_derived : base
{
    virtual void foo() const override { std::cout << "also_derived::foo\n" ; }
};

struct more_derived : derived
{
    virtual void foo() const override { std::cout << "more_derived::foo\n" ; }
};

int main()
{
    const derived a, b ;
    const also_derived c, d ;
    const more_derived e, f ;

    const base* objects[] { &a, &c, &e, &f, &b, &d } ;
    for( auto ptr : objects ) ptr->foo() ;
}
