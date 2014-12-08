#include <iostream>

void funz( int*& a )
{
    static int b = 45 ;
    a = &b ;
}

int main()
{
    int i = 777 ;
    int* pi = &i ;
    std::cout << "int at address " << pi << " has value " << *pi << '\n' ;
    
    funz(pi) ;
    std::cout << "int at address " << pi << " has value " << *pi << '\n' ;
}


