#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> seq { 6, 21, 7, 3, 10 } ;

    if( seq == std::vector<int>{ 3, 6, 7, 10, 21 } ) std::cout << "equal\n" ;
    else std::cout << "not equal\n" ;

    std::sort( std::begin(seq), std::end(seq) ) ;

    if( seq == std::vector<int>{ 3, 6, 7, 10, 21 } ) std::cout << "equal\n" ;
    else std::cout << "not equal\n" ;
}
