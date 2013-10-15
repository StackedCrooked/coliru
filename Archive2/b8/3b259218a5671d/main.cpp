#include <iostream>

struct A
{
    A( double v ) : value(v) {}
    ~A()
    {
        std::cout << "A::destructor - value: " << value << "  address of value: " << &value
                   << "\n   any reference to this object is now a dangling reference\n\n" ;
        value = -1 ;
    }
    double value ;
};

struct reftest
{
    const double& refval;
    reftest(const A& rrt):refval(rrt.value) { std::cout << "constructor of reftest exits now\n\n" ; }
};

reftest rr( A(47.0) );

int main()
{
    std::cout << "we have entered main now\n" ;
    std::cout << "address of object referred to by rr.refval is: " << &(rr.refval) << '\n' ;
}
