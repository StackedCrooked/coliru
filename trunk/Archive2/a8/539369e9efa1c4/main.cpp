#include <iostream> // #include <stdio.h>
//#include <stdlib.h>
#include <cmath> // #include <math.h>
// #include <stdbool.h>
#include <iomanip>

bool is_prime( int n )
{
    if( n < 2 ) return false ;
    if( n == 2 ) return true ;
    if( n%2 == 0 ) return false ;

    const int iroot = std::lround( std::sqrt(n) ) + 1 ;

    for( int k = 3 ; k < iroot ; k += 2 ) if( n%k == 0 ) return false ;

    return true ;
}


int main()
{
    /*  (this is not even C)
    bool Prime(int A)
    {
        int k;
        if (A == 2)
        {
            return true;
        }
        for (k = 0; k < (int)sqrt(A); k++)
        {
            if ( A % (k+2) == 0)
            {
                return false;
            }
        }
                return true;
    }
    */


    //int start, end, max, j;
    // start = 101;
    // end   = 150;
    // if (start < 2) { start = 2; }
    // max = end - (start - 1);
    const int start = 101 ;
    const int end = 150 ;

    // for(j = 0; j < max; j++)
    //{
      //  if( Prime(j+start))
      //  {
      //  printf("\t\t\t\t    %4d\n",j+start);
      //  }
    // }
    std::cout << "prime numbers in [" << start << ',' << end << ")\n" ;
    for( int j = start ; j < end ; ++j )
        if( is_prime(j) ) std::cout << std::setw(16) << j << '\n' ;
}
