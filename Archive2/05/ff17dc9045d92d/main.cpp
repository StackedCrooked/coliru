#include <iostream> 

constexpr int func1( int x ) ;

constexpr int func2( int x )
{
    
    return x <= 0 ? -20 : func1( x - 1 ) ;
}

//constexpr int y = func1( 10 ) ;

constexpr int func1( int x )
{    
    return x <= 0 ? -10 : func2( x - 1 ) ;
}

int main()
{
    constexpr int z = func1( 10 ) ;
    
    std::cout << z << std::endl ;
}