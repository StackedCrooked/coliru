#include <iostream>
#include <bitset>
#include <limits>

int main()
{
    constexpr int i = std::numeric_limits<int>::min() ;

    const std::bitset< std::numeric_limits<int>::digits > bad(i) ;
    std::cout << bad << '\n' ;

    const std::bitset< std::numeric_limits<unsigned int>::digits > good(i) ;
    std::cout << good << '\n' ;
}
