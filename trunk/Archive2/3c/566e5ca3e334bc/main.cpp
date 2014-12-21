#include <iostream>

int main()
{
    double x1 = 0, x2 = 0 ;
    
    int t = { int( x1 + x2 ) } ; // fine
    
    t = { x1 + x2 } ; // **** error: implicit narrowing conversion
    
    return t ;
}
