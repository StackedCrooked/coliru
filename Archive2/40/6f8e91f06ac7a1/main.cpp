#include <iostream>
#include <string>
#include <typeinfo>
 
struct Base {}; // non-polymorphic
struct Derived : Base {};
 
struct Base2 { virtual void foo() {} }; // polymorphic
struct Derived2 : Base2 {};
 
int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}