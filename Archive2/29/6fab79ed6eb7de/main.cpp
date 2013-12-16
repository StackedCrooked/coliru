#include <iostream>
#include <valarray>

int main()
{
    // http://en.cppreference.com/w/cpp/numeric/valarray
    
    std::valarray<unsigned int> a = { 1, 2, 3, 4 } ;
    std::valarray<unsigned int> b = { 5, 6, 7, 8 } ;

    std::valarray<unsigned int> c = a * b ;
    for( auto i : c ) std::cout << i << ' ' ;
    std::cout << '\n' ;

    std::valarray<unsigned int> d = a * ( b + 10U ) ;
    for( auto i : d ) std::cout << i << ' ' ;
    std::cout << '\n' ;
}
