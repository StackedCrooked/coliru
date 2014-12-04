#include <cstddef>
#include <stdexcept>

class str_const {
    const char * const p_;
    const std::size_t sz_;
public:
    template <std::size_t N>
    constexpr str_const( const char( & a )[ N ] )
    : p_( a ), sz_( N - 1 ) {}
    constexpr char operator[]( std::size_t n ) const {
        return n < sz_ ? p_[ n ] : throw std::out_of_range( "" );
    }
    constexpr std::size_t size() const { return sz_; }
};

constexpr long int numOpen( const str_const & str ){
    long int numOpen{ 0 };
    std::size_t idx{ 0 };
    while ( idx <  str.size() ){
        if ( str[ idx ] == '{' ){ ++numOpen; }
        else if ( str[ idx ] == '}' ){ --numOpen; }
        ++idx;
    }
    return numOpen;
}

constexpr bool check( const str_const & str ){
    const auto nOpen = numOpen( str );
    // ...
    // Apply More Test functions here,
    // each returning a variable encoding the correctness of the input
    // ...

    return ( nOpen == 0 /* && ... Test the variables ... */ );
}

int main() {
    constexpr str_const s1{ "{ Foo : Bar } { Quooz : Baz }" };
    constexpr auto pass = check( s1 );
}