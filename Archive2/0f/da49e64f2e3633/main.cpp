#include <iostream>

int main()
{
    int a[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 } ;
    
    again: for( int& v : a )
           {
               ++v ;
               if( v%2 == 1 ) goto again ;
               else v += 2 ;
           }
    
    for( int& v : a ) std::cout << v << ' ' ;
}
