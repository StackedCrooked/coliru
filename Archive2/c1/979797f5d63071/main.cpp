#include <cstddef>
#include <iostream>
 
void f(int* pi)
{
   std::cout << "Pointer to integer overload\n";
}
 
void f(double* pd)
{
   std::cout << "Pointer to double overload\n";
}
 
void f(std::nullptr_t nullp)
{
   std::cout << "null pointer overload\n";
}
 
int main()
{
    int* pi; double* pd;
 
    f(pi);
    f(pd);
    f(nullptr);  // would be ambiguous without void f(nullptr_t)
    // f(NULL);  // ambiguous overload: all three functions are candidates
}