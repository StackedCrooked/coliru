#include <iostream>
#include <cstdint>

int main()
{
    int x = 4;
    int* p1 = &x;
    int** p2 = &p1;
    
    // ok olha aqui viado
    int* r1 = *p2;
    int* r2;
    r2 = (int*)p2;
    r2 = *(int**)p2;

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;
    std::cout << p1 << std::endl;
    std::cout << *r2 << std::endl;
}