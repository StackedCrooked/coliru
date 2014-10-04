#include <list>
#include <iostream>
#include <ctime>

int main( int argc, char*[] )
{
    std::size_t n = 8 * 1024 * 1024 * argc ;
    std::list<int> lst(n) ;
    
    const auto start = std::clock() ;
    int v = 0 ;
    for( int i = 0 ; i < 100 ; ++i ) 
    {
        lst.push_back(i) ;
        v += lst.size() ;
    }
    const auto end = std::clock() ;
    
    std::cout << (end-start) * 1000.0 / CLOCKS_PER_SEC << " millisecs\n\n" ;
    
    return v < 0 ;
}
