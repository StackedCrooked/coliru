#include <iostream>
#include <typeinfo>
 
struct S { // The type has to be polymorphic
    virtual void f();
}; 
 
int main()
{
    S* p = nullptr;
    try {
        std::cout << typeid(*p).name() << '\n';
    } catch(const std::bad_typeid& e) {
        std::cout << e.what() << '\n';
    }
}