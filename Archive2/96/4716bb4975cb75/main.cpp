#include <iostream>
#include <cstdlib>
#include <ctime>

void populateArray( int ar[], /*const*/ int n )
{
    for( int i = 0 ; i < n ; ++i ) ar[i] = std::rand() % 50 + 1 ;
}

int main()
{
    // http://en.cppreference.com/w/cpp/numeric/random/srand
    std::srand( std::time(nullptr) ) ; // **** important ****

    const int ARRAY_SIZE = 50;
    int ar[ARRAY_SIZE] = {0} ;

    populateArray( ar, ARRAY_SIZE ) ;

    for( int v : ar ) std::cout << v << ' ' ;
}
