#include <iostream>

int main()
{
    int i = -1 ;
    std::cout << i << ' ' << unsigned(i) << '\n' ;
    i >>= 2 ;
    std::cout << i << ' ' << unsigned(i) << "\n\n" ;
    
    unsigned int u = -1 ;
    std::cout << signed(u) << ' ' << u << '\n' ;
    u >>= 2 ;
    std::cout << signed(u) << ' ' << u << '\n' ;
}
