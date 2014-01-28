#include <iostream>

static const std::size_t ARRAY_SZ = 8 ;

using array_type = int[ARRAY_SZ] ;

array_type& array() ;

int test = array()[3] ;

int main()
{
    for( int v : array() ) std::cout << v << ' ' ; // 4
    std::cout << '\n' << "test: " << test << '\n' ;
}

// in some translation unit

#include <random>

array_type& array()
{
     static array_type a{} ;

     // one-time initialization of a with values known only at run-time
     static std::random_device rand_dev ;
     static std::mt19937 mt( rand_dev() ) ;
     static std::uniform_int_distribution<int> distr( 100, 999 ) ;
     static int init = [&]() { for( int& v : a ) v = distr(mt) ; return 1 ; }() ;
     (void)init ; // to suppress unused variable diagnostic
     
     return a ;
}
