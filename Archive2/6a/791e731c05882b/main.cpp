#include <iostream>
#include <ctime>

int count_bits( unsigned int n ) ; 

int count_bits_inlined( unsigned int n )
{
    if( n == 0 ) return 0 ;
    else return n%2 + count_bits_inlined( n/2 ) ;
}


int main()
{
    unsigned int MAX = 1024*1024*16 ;
    
    {
        long long cnt = 0 ;
        
        auto begin = clock() ;
        for( unsigned int i = 0 ; i < MAX ; ++i ) cnt += count_bits_inlined(i) ;
        auto end = clock() ;
        
        std::cout << "count: " << cnt << "        inlined: " << double(end-begin) / CLOCKS_PER_SEC << " seconds\n" ;
    }
    
    {
        long long cnt = 0 ;
        
        auto begin = clock() ;
        for( unsigned int i = 0 ; i < MAX ; ++i ) cnt += count_bits(i) ;
        auto end = clock() ;
        
        std::cout << "count: " << cnt << "    not inlined: " << double(end-begin) / CLOCKS_PER_SEC << " seconds\n" ;
    }
}
