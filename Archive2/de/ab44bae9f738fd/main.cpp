#include <iostream>
#include <string>

struct A {
    int n;
    A(int n=1) : n(n) { std::cout << "A::Default constructor" << std::endl; }
    A(const A& a) : n(a.n) { std::cout << "A::Copy constructor" << std::endl; } // user-defined copy ctor
    A& operator=(A other) {
        std::cout << "A:: assignment\n";
        std::swap(n, other.n);
        return *this;
    }
};
 
struct B : A {
    // implicit default ctor B::B()
    // implicit copy ctor B::B(const B&) 
};

A createA(unsigned int n)
{
    return A(n);
}


int main(void)
{
    
    A a1(1);
    
    std::cout << "=================================" << std::endl;
    
    const A& a2 = createA(2); 
    
    std::cout << "=================================" << std::endl;
    
    // A& a3 = createA(3);  => Does not compile
    
    std::cout << "=================================" << std::endl;
    
    A a4 = createA(4); 
    
    std::cout << "=================================" << std::endl;
}