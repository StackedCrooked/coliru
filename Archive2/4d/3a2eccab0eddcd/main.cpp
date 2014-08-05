#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <functional>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

typedef std::map< int, std::string >    my_map_t;
typedef std::vector< int >              int_vec_t;

template< size_t size >
struct game_traits
{
    enum{ board_size = size };
};

template< template<size_t> class traits >
struct check
{
    
};

int unique( void ) 
{
    static int __loc = 0;
    return __loc++;
}

#include <iostream>
 
struct C {
  C() {}
  C(const C&) { std::cout << "A copy was made.\n"; }
};
 
C f() {
  return C();
}
 
int main() {
  std::cout << "Hello World!\n";
  C obj = f();
}

/*int main()
{
    //my_map_t my_map;
    //int_vec_t my_vec;    
    int_vec_t my_primes;
    
    // std::generate_n( std::back_inserter( my_primes ), 12, &unique );
    
    // generate
    std::generate_n( std::back_inserter( my_primes ), 16, []( void ){ static int __i = 2; return __i++ * 2 - 1; } );

    // sieve
    for( auto it = my_primes.begin(); it != my_primes.end() - 1; ++it )
    {
        std::remove_if( it + 1, my_primes.end(), [=]( int i ){ return ( i % 3 ) == 0; } );
    }
    
    // print the result
    std::copy( 
          my_primes.begin()
        , my_primes.end()
        , std::ostream_iterator< int >( std::cout, ", " ) );
            
    /*std::copy_if( my_vec.begin(), my_vec.end(), std::ostream_iterator< int >( std::cout, ", " ), [](int i){return (i&(i-1)) == 0;} );
            
    for( auto el = 0; el < 10; ++el )
    {
        my_map.insert( std::make_pair( el, std::string( "the number is: " ) + std::to_string( el * 1000 ) ) );    
    }
    
    std::transform( 
          my_map.begin()
        , my_map.end()
        , std::ostream_iterator< std::string >( std::cout, "\n" )
        , std::bind( &my_map_t::value_type::second, std::placeholders::_1 ) );    
}*/
