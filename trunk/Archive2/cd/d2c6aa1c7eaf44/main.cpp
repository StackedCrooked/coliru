#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // std::srand elided
    const int a[15] =  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 9, 4, 4, 4 } ;
    std::vector<int> seq( a, a+15 ) ;
    std::random_shuffle( seq.begin(), seq.end() ) ;
    for( std::size_t i = 0 ; i < seq.size() ; ++i ) std::cout << seq[i] << ' ' ;
    std::cout << '\n' ;

    const std::vector<int>::iterator iter_min = std::min_element( seq.begin(), seq.end() ) ;
    const int min_element = *iter_min ;
    const std::size_t min_element_pos = iter_min - seq.begin() ;

    const std::vector<int>::iterator iter_max = std::max_element( seq.begin(), seq.end() ) ;
    const int max_element = *iter_max ;
    const std::size_t max_element_pos = iter_max - seq.begin() ;

    std::cout << "min element " << min_element
              << " first occurrence at " << min_element_pos << '\n'

              << "max element " << max_element
              << " last occurrence at " << max_element_pos << '\n' ;
}
