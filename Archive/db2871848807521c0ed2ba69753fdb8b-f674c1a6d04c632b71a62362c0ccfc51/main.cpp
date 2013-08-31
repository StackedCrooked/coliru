#include <iostream>

void foo(bool x = !(std::cout << "foo\n")) {}

int main()
{
    foo();
    
}