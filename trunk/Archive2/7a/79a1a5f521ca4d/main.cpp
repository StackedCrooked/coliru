#include <vector>

int foo( const std::vector<int>& seq )
{
    int s = 0 ;
    for( std::size_t i  = 0 ; i < seq.size() ; ++i ) s += seq[i] ;
    return s ;
}

int bar( const int carray[], std::size_t size )
{
    int s = 0 ;
    for( std::size_t i  = 0 ; i < size ; ++i ) s += carray[i] ;
    return s ;
}
