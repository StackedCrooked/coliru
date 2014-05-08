#include <iostream>


struct Base
{
    virtual ~Base() {}
    
    int n;
};

struct Derived: virtual Base { };



int main()
{
    Derived* d = new Derived;
    Base* b = d;    
    
    std::cout << std::boolalpha;
    std::cout << "Real addresses:" << std::endl;
    std::cout << "    derived: " << d << std::endl;
    std::cout << "       base: " << b << std::endl;
    std::cout << " difference: " << ((long)b - (long)d) << std::endl;
    
    
    std::cout << "\nCompiler logic:" << std::endl;
    std::cout << " derived == base // returns " << (d == b) << std::endl;
    
    
    std::cout << "\nWithout type info:" << std::endl;
    std::cout << " (void*)derived == (void*)base // returns " << ((void*)d == (void*)b) << std::endl;
}