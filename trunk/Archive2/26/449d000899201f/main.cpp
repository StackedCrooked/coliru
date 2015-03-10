#include <iostream>
#include <malloc.h>
#include <utility>
#include <vector>
#include <algorithm>

int main()
{
    const int N = 5'000'000 ;

    {
        using point = std::pair<int,int> ;
        
        std::vector<point> vec ;
        vec.reserve( N * 1.25 ) ;
        for( int i = 0 ; i < N ; ++i ) vec.emplace_back( i, N-i ) ;
        std::sort( vec.begin(), vec.end() ) ;
        
        std::cerr << "\nint\n---\n" ;
        malloc_stats() ;
    }

    {
        using point = std::pair<double,double> ;
        
        std::vector<point> vec ;
        vec.reserve( N * 1.25 ) ;
        for( int i = 0 ; i < N ; ++i ) vec.emplace_back( i, N-i ) ;
        std::sort( vec.begin(), vec.end() ) ;
        
        std::cerr << "\n\ndouble\n---\n" ;
        malloc_stats() ;
    }
}
