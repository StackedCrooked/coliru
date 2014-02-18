#include <iostream>
#include <vector>

std::vector< std::vector<int> > create_square_matrix( std::size_t m )
{ return std::vector< std::vector<int> >( m, std::vector<int>(m) ) ; }

int main()
{
    int m;
    std::cin >> m;

    auto A = create_square_matrix(m) ;

    for( int i = 0 ; i < m ; ++i )
    {
        for( int j = 0 ; j < m ; ++j ) std::cout << A[i][j] << ' ' ;
        std::cout << '\n' ;
    }
}
