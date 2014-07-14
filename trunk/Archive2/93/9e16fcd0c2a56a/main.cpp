#include <iostream>
#include <limits>

int main()
{
    int a  = std::numeric_limits<int>::max() ;
    const int b = a ;
    std::cout << "a == " << a << "  b == " << b << '\n' ; 
    
    std::cout << "just before engendering undefined behaviour\n" << std::flush ;
    ++a ; // *** engenders undefined behaviour ***
    std::cout << "after ++a, " ;
    
    if( a == b ) std::cout << "a is equal to b\n" ;
    else if( a > b ) std::cout << "a is greater than b\n" ;
    else std::cout << "a is less than b\n" ;
}
