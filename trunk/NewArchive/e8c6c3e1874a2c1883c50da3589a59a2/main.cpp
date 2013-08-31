#include <iostream>
 
struct S { void (*f)(); };

int main()
{
    S s = S();
    if ( s.f == NULL)
       std::cout << "s.f is NULL" << std::endl;
}