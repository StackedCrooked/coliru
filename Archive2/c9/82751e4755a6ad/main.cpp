#include <unordered_map>
#include <iostream>

template < typename T >
using vector = std::unordered_map< std::size_t, T > ;

int main ()
{
    vector< vector< vector<int> > > vecs ;

    vecs[9999][19999][229999] = 9 ;
    vecs[5555][4444][3333] = 543 ;
    vecs[100][88888888][25] = 1234 ;
    // etc

    int sum = 0 ;
    for( const auto& p1 : vecs )
        for( const auto& p2 : p1.second )
            for( const auto& p3 : p2.second ) sum += p3.second ;
    std::cout << sum << '\n' ;
}
