#include <type_traits>
#include <cstddef>
#include <array>


template <std::size_t nrank>
struct index {
    std::array<std::ptrdiff_t, nrank> res;
    
    index( std::ptrdiff_t dim ) {
        static_assert( nrank == 1, "You cannot construct an index with a single argument when the rank is not 1" );
    	res[ 0 ] = dim;
    }
    
    index( std::size_t dim ) {
    	static_assert( nrank == 1, "You cannot construct an index with a single argument when the rank is not 1" );
    	res[ 0 ] = dim;
    }
    
    template <typename T, typename = typename std::enable_if<!( std::is_integral<typename unqualified<T>::type>::value )>::type>
    index( T&& values ) {
    	std::copy( values.begin( ), values.end( ), res.begin( ) );
    }
}

int main () {
   
}