#include <iostream>

enum E
{
    A, B, C
};

int main()
{
    int x = A;
    E y = static_cast<E>(x);
    
    switch(y)
    {
        case A: std::cout << "A" << std::endl; break;
        case B: std::cout << "B" << std::endl; break;
        case C: std::cout << "C" << std::endl; break;
        default: break;
    }
    
    return 0;
}