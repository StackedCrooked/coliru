#include <iostream>
#include <memory>

struct A 
{
    A() { std::cout << "A constructed at " << this << '\n' ; }
    A( const A& that ) { std::cout << "A copy constructed from " << &that << " to " << this << '\n' ; }
    ~A() { std::cout << "A at " << this << " destroyed\n" ; }
};

std::unique_ptr<A> foo() { 
    std::unique_ptr<A> ok(new A);
    return ok;
}

int main()
{
    { auto p = foo() ; }
    std::cout << "-------------------\n" ;
    
    {
        std::unique_ptr<A> fine(new A);
        fine = std::unique_ptr<A>(new A);
    }
    std::cout << "-------------------\n" ;
}
