#include <iostream>
#include <string>
#include <type_traits>

template < typename T> std::string debug_rep( const T& arg )
{
    static_assert( std::is_same< decltype(arg), std::string* const& >::value, "expected std::string* const&" ) ;
    std::cout << "type of arg is std::string* const&\n" ;
    return "" ;
}

int main()
{
    std::string s( "hi" ); // type of s is std::string

    // type of std::addressof(s) is 'pointer to std::string' ie. std::string*
    // type of &s is 'pointer to std::string' ie. std::string*
    // using pstr_t = std::string* ; // type pstr_t is 'pointer to std::string' ie. std::string*

    debug_rep(&s) ; // instantiate function template std::string debug_rep<X>( const X& arg )
                    // where the type X is the type of the expression &s
                    // ie where the type X is pstr_t; std::string debug_rep<pstr_t>( const pstr_t& arg )
                    // ie. std::string debug_rep( std::string* const& arg );
                    // type of arg is 'const pointer to (non-cost) std::string' or std::string* const&
                    
}
