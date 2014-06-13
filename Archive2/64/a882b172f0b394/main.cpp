#include <iostream>
#include <typeinfo>


struct Base  { virtual ~Base() {} };
struct Derived : Base  {};


int main()
{
    Derived derived;
    Base& base = derived;    
    std::cout << typeid(base).name() << std::endl;
}
