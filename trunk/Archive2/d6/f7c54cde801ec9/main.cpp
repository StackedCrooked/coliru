#include <iostream>

int main()
{
    for( unsigned int N = 1 ; N < 5000 ; ++N )
        if( ( N & (N-1) ) == 0 ) std::cout << N << ' ' ;
}
