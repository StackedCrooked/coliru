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

    std::cout << "min element " << *pair.first
               << " first occurrence at " << pair.first - seq.begin() << '\n'

               << "max element " << *pair.second
               << " last occurrence at " << pair.second - seq.begin() << '\n' ;
}
