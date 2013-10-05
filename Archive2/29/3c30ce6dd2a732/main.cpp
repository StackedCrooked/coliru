#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

std::vector<int> ints_in_reverse( const std::string& str )
{
    std::istringstream stm(str) ; // input stringstream to read from the line

    // create a vector containing inters in the line (left to right)
    using iterator = std::istream_iterator<int> ;
    std::vector<int> seq { iterator(stm), iterator() } ;

    std::reverse( std::begin(seq), std::end(seq) ) ; // reverse the vector

    return seq ; // and return it
}

std::vector< std::vector<int> > reverse_read_lines( std::istream& stm )
{
    std::vector< std::vector<int> > result ;
    std::string line ;

    while( std::getline( stm, line ) ) result.push_back( ints_in_reverse(line) ) ;

    return result ;
}

int main()
{
    std::istringstream file( " 3 9 8 7 6\n"
                             "4 1 2 3 4 5\n"
                             "0 1 2 3 4 5 6 7 8 9\n" ) ;

    const auto vectors = reverse_read_lines(file) ;

    for( const auto& line : vectors )
    {
        for( int v : line ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
}
