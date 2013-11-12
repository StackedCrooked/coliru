#include <iostream>

struct base
{
    virtual ~base() {}

    void foo() const
    {
        std::cout << "base::foo -       const base* this points to " << this << '\n' ;
        this->bar() ;
    }

    virtual void bar() const = 0 ;
};

struct filler { virtual ~filler() {} char fill[1234] ; } ;

struct derived : filler, base
{
   virtual void bar() const override
   { std::cout << "derived::bar - const derived* this points to " << this << '\n' ; }
};

int main()
{
    derived d ;
    base& b = d ;
    b.foo() ;
}
