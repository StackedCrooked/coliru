#include <iostream>


struct Item {};

template<typename T>
void foo(T&)
{
}


int main()
{
    const Item a;
    foo(a); // OK
    
    foo(Item{}); // Error
}