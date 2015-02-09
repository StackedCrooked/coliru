#include <iostream>
#include <algorithm>
#include <string>

template< typename value_type >
auto make_case( value_type in_v ) {
    struct {
        value_type value;

        bool operator () ( value_type const & t ) { return t == value; }
        bool operator () ( std::initializer_list< value_type > ts )
            { return std::find( ts.begin(), ts.end(), value ) != ts.end(); }
    } ret{ std::move( in_v ) };
    return ret;
}

int main() {
    std::string s = "Mary";
    
    auto s_case = make_case( s );
    if ( s_case({ "Bob", "Dave" }) )
        { std::cout << "It's a boy!\n"; }
    else if ( s_case( "Mary" ) )
        { std::cout << "It's a girl!\n"; }
    
    auto c_case = make_case( s[ 0 ] );
    if ( c_case({ 'D', 'M', 'X' }) )
        { std::cout << "Probably named after a rapper.\n"; }
    else if ( c_case({ 'Q' }) )
        { std::cout << "Probably British.\n"; }
    else if ( std::islower( c_case.value ) )
        { std::cout << "A very humble name."; }
    else
        { std::cout << "AI failure.\n"; }
}
