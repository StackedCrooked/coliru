#include <vector>
#include <array>

int foo( const std::vector<int>& vector )
{
    int s = 0 ;
    for( std::size_t i  = 0 ; i < vector.size() ; ++i ) s += vector[i] ;
    return s ;
}

int foo( const int carray[], std::size_t size )
{
    int s = 0 ;
    for( std::size_t i  = 0 ; i < size ; ++i ) s += carray[i] ;
    return s ;
}

constexpr std::size_t N = 1024*1024*128 ;

int foo( const std::array< int, N >& stdarray )
{
    int s = 0 ;
    for( std::size_t i  = 0 ; i < stdarray.size() ; ++i ) s += stdarray[i] ;
    return s ;
}

