#include <iostream>
#include <string>
#include <numeric>

struct name
{
    explicit name( std::string str ) : id(str) {}

    operator std::string() const { return id ; }

    name& operator++()
    {
        if( id.size() > 1 )
        {
            if ( id [ 1 ] < '9' ) id [ 1 ]++;
            else
            {
                id [ 0 ]++;
                id [ 1 ] = '1';
            }
        }
        return *this ; // return next name in order
    }

    private: std::string id ;
};


int main()
{
    constexpr std::size_t N = 5 ;
    std::string a[N] ;

    // http://en.cppreference.com/w/cpp/algorithm/iota
    std::iota( a, a+N, name( "A1") ) ;
    for( const auto& s : a ) std::cout << s << '\n' ;
}
