#include <iostream>
#include <utility>

int main()
{
    constexpr std::size_t N = 5 ;

    std::pair<int,int> my_legacy_array[N] { {}, {31,24}, {51,26}, {71,28} } ;
    my_legacy_array[0] = { 15, 26 } ;
    my_legacy_array[N-1] = { 98, 99 } ;

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( const auto& p : my_legacy_array ) std::cout << '{' << p.first << ',' << p.second << "} " ;
    std::cout << '\n' ;
}
