#include <iostream>
#include <chrono>
#include <cstddef>

constexpr std::size_t factorial1( std::size_t n )
{
    return n <= 1 ? 1 : ( n * factorial1( n - 1 ) );
}

std::size_t factorial2( std::size_t n )
{
    return n <= 1 ? 1 : ( n * factorial2( n - 1 ) );
}
 
int main()
{
    auto start1 = std::chrono::high_resolution_clock::now();
    constexpr std::size_t f1 = factorial1( 30 );
    auto stop1 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast< std::chrono::nanoseconds >( stop1 - start1 ).count() << std::endl;
    
    auto start2 = std::chrono::high_resolution_clock::now();
    const std::size_t f2 = factorial1( 30 );
    auto stop2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast< std::chrono::nanoseconds >( stop2 - start2 ).count() << std::endl;
    
    return EXIT_SUCCESS;
}