#include <iostream>
#include <functional>

struct base
{
    virtual void foo() { std::cout << "base\n"; }
    virtual ~base() {}
};

struct derived : public base
{
    void foo() { std::cout << "derived\n"; }
};

int main()
{
    std::cout << "using bind : ";
    derived d;
    auto f = std::bind (&base::foo, &d);
    f ();
    
    std::cout << "using function pointer : ";
    typedef void (base::*fp)();
    fp p = &base::foo;
    (d.*p) ();
}