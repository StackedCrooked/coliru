#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> seq { 4, 9, 2, 8, 1, 3, 0, 6, 7, 5} ;
    const auto begin = std::begin(seq) ;
    const auto end = std::end(seq) ;
    
    std::cout << "smallest element: " 
              << *std::min_element( begin, end ) << '\n' ; 
              
    std::cout << "position of smallest element: " 
              << std::min_element( begin, end ) - begin << '\n' ; 
    
    constexpr std::size_t n = 5 ;
    std::nth_element( begin, begin+n,  end ) ;
    std::cout << "the smallest " << n << " elements are: " ;
    for( std::size_t i = 0 ; i < n ; ++i ) std::cout << seq[i] << ' ' ;
    std::cout << '\n' ;
}