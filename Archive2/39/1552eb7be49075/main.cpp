#include <iostream>

int main()
{
    int n = 10 ;

    for( int i = 0 ; i < n*2 ; ++i ) // i in [ 0 1 2 ... 8 9 10 11 12 ... 18 19 ]
    {
        int nstars = i%n + 1 ;  // nstars in [ 1 2 3 ... 9 10 1  2  3...   9 10 ]
        for( int j = 0 ; j < nstars ; ++j ) std::cout << '*' ;
        std::cout << '\n' ;
    }
}
