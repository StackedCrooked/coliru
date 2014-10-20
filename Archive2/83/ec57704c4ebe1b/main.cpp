#include <iostream>

int main()
{
    int n = 10 ;
    int ntriangles = 2 ;
    
    for( int i = 0 ; i < ntriangles ; ++i )
    {
        for( int a = 1 ; a <= n ; ++a )
        {
            for( int b = 1 ; b <= a ; ++b ) std::cout << '*' ;
            std::cout << '\n' ;
        }
    }
}
