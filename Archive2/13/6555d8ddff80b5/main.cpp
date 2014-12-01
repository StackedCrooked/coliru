#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

std::vector<double> fill_vector( std::istream& stm ) // return by value
{
    std::vector<double> vec ;
    double d ;
    while( stm >> d ) /*if( !std::isnan(d) )*/ vec.push_back(d) ;
    return vec ;
}

// invariant: sequence does not contain NaNs
void selection_sort( std::vector<double>& seq, std::size_t from_pos = 0 )
{
    if( from_pos < seq.size() )
    {
        const auto iter_from =  seq.begin() + from_pos ;

        // http://en.cppreference.com/w/cpp/algorithm/min_element
        const auto iter_smallest = std::min_element( iter_from, seq.end() ) ;

        // http://en.cppreference.com/w/cpp/algorithm/iter_swap
        std::iter_swap( iter_from, iter_smallest ) ; // std::swap( *iter_from, *iter_smallest ) ;

        selection_sort( seq, from_pos+1 ) ;
    }
}

int main()
{
    std::istringstream stm( "3 9 8 2 9 1 6 4 8 5 7 4 3 6 6 3 9 2" ) ;

    auto seq = fill_vector(stm) ;
    const std::size_t number_used = seq.size() ;
    std::cout << number_used << " numbers were read\n" ;

    selection_sort(seq) ;
    for( double d : seq ) std::cout << d << ' ' ;
}
