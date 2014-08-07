#include <iostream>
#include <array>

template < typename MATRIX > void print( const MATRIX& matrix )
{
    for( const auto& row : matrix )
    {
        for( const auto& v : row ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
    std::cout << "-------\n" ;
}

int main()
{
    std::array< std::array< char, 3 >, 3 > matrix = { { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} } };
    print(matrix) ;

    matrix = { { {'A', 'B', 'C'}, {'D', 'E', 'F'}, {'G', 'H', 'I'} } } ;
    print(matrix) ;

    matrix = { { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} } } ;
    print(matrix) ;
}
