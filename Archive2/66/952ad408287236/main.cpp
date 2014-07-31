#include <iostream>


struct A
{
    A() : name("A") {}
    const char* name;
};


struct B : A
{
    B() : name("B") {}
    const char* name;
};


int main()
{
    A* a = new A;
    B* b = new B;
    
    std::cout << *(const char**)(B*)a << std::endl;
    std::cout << *(const char**)(A*)b << std::endl;
}
