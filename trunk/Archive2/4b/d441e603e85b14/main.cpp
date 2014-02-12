#include <iostream>
#include <cstdlib>

struct alignas(8) big
{
   int array [1000];
};

big foo( const big& ) ;

int main()
{
    std::srand(123456) ;
    int x = 0 ;
    big b ;
    
    for( int i = 0 ; i < 1000*1000 ; ++i ) x += foo(b).array[0]%2 ;
    std::cout << x << '\n' ; // statistically expected value: 500000
}
