#include <iostream>
#include <ctime>
#include <boost/pool/pool_alloc.hpp>
#include <deque>
#include <memory>

template < std::size_t N > struct A { char filler[N] ; };

template < std::size_t N > struct B final
{
    A<N> a ;

    static void* operator new ( std::size_t ) { return pool.malloc() ; }
    static void operator delete ( void* p ) { pool.free(p) ; }

    private:
        struct big_chunk_allocator
        {
          using size_type = std::size_t ;
          using difference_type = std::ptrdiff_t ;

          static char* malloc( size_type sz ) { return new char[sz] ; }
          static void free( const char* p ) { delete [] p ; }
        };

        static boost::pool<big_chunk_allocator> pool ;
};

template < std::size_t N >
boost::pool< typename B<N>::big_chunk_allocator > B<N>::pool( sizeof( B<N> ) ) ;

template < typename T > void test( std::size_t n = 1024*1024 )
{
    const auto start = std::clock() ;
    {
        std::deque< std::unique_ptr<T> > seq(n/4) ;

        while( seq.size() < n )
        {
            const auto sz = seq.size() ;
            for( std::size_t i = 0 ; i < sz ; ++i ) seq.emplace_back( new T ) ;
            seq.erase( seq.begin(), seq.begin() + sz/4 ) ;
        }
    }

    const auto end = std::clock() ;
    std::cout << double(end-start) / CLOCKS_PER_SEC << " secs.\n" ;
}

template < std::size_t N > void do_test()
{
    static_assert( sizeof( A<N> ) == N, "check size" ) ;
    static_assert( sizeof( B<N> ) == N, "check size" ) ;

    std::cout << "size: " << N << "\n\tdefault allocation: " ;
    test< A<N> > () ;

    std::cout <<  "\t   pool allocation: " ;
    test< B<N> > () ;

    std::cout << '\n' ;
}

int main()
{
    std::cout << std::fixed ;
    std::cout.precision(3) ;

    do_test<12>() ;
    do_test<16>() ;
    do_test<24>() ;
    do_test<48>() ;
    do_test<64>() ;
    do_test<96>() ;
    do_test<128>() ;
}
