#include <iostream>

int main()
{
    double x = 3.141592;
    char mem[100];
    std::uintptr_t p = (uintptr_t)mem;
    p = p + (p&~(uintptr_t)7) + 17;
    double *y = (double *)p;
    *y = x;
    std::cout << *y << '\n' ;
}
