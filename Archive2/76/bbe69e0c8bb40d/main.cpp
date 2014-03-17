#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // std::srand elided

    std::vector<int> seq { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 9, 4, 4, 4 } ;
    std::random_shuffle( seq.begin(), seq.end() ) ;
    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    // http://en.cppreference.com/w/cpp/algorithm/minmax_element
    const auto pair = minmax_element( seq.begin(), seq.end() ) ;

    const int min_element = *pair.first ;
    const std::size_t min_element_pos = pair.first - seq.begin() ;

    const int max_element = *pair.second ;
    const std::size_t max_element_pos = pair.second - seq.begin() ;

    std::cout << "min element " << min_element
              << " first occurrence at " << min_element_pos << '\n'

              << "max element " << max_element
              << " last occurrence at " << max_element_pos << '\n' ;
}
