#include <iostream>
#include <boost/variant.hpp>
#include <boost/variant/polymorphic_get.hpp>

struct A
{
    virtual ~A(){}
    virtual void foo() { }
};
struct B : A
{
    virtual void foo() { std::cout << "B::foo()" << std::endl; }
};

int main()
{
    typedef boost::variant<A*,B*> MyVar;
    MyVar var = new B;
    B* a = boost::polymorphic_get<B*>(var);
    a->foo();
}
