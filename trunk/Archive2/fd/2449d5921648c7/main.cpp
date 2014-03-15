#include <vector>

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

