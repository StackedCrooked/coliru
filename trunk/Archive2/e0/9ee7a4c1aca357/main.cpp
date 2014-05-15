#include <iostream>
#include <vector>

int main ()
{
    std::size_t n ;
    std::cin >> n ;

    std::vector< std::vector<long> > main_vec(n) ; // vector of vectors
    for( std::size_t i = 0 ; i < n ; ++i ) main_vec[i].resize(i+1) ;

    for( const auto& row : main_vec )
    {
        for( long v : row ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
}
