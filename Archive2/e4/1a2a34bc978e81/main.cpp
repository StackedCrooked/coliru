#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>

// remove k characters from str to yield the lexicographically largest string
std::string delete_k_verbose( const std::string& str, std::size_t k )
{
    if( k == 0 ) return str ;
    else if( k >= str.size() ) return "" ;

    // search currect k span for largest value
    const auto iter = std::max_element( str.begin(), str.begin() + k+1 ) ;
    const auto pos = iter - str.begin() ;

    // rest of the string after the largest
    const std::string tail = str.substr(pos+1) ;

    // number of characters still to be removed
    auto n_left = k - pos ;

    // tail after removing n_left characters
    const std::string shortened_tail = delete_k_verbose( tail, n_left ) ;

    // the result string is: this character + shortened tail
    return *iter + shortened_tail ;
}

std::string delete_k( const std::string& str, std::size_t k )
{
    if( k == 0 ) return str ;
    else if( k >= str.size() ) return "" ;

    const auto iter = std::max_element( str.begin(), str.begin() + k+1 ) ;
    const auto pos = iter - str.begin() ;

    return *iter + delete_k( str.substr(pos+1), k-pos ) ;
}

std::string delete_k_bgdanghe( std::string str, std::size_t k )
{
    if( k >= str.size() ) return "" ;

    // start at the beginning
    auto begin = str.begin() ;
    while(k)
    {
        // search currect k span for largest value
        auto iter_largest = std::max_element( begin, begin + k+1 ) ;

        // mark for deletion every letter in front of largest value
        std::fill( begin, iter_largest, 0 ) ;

        k -= iter_largest - begin ; // update k

        // position start marker after largest value
        begin = iter_largest + 1 ;
    }

    // finally delete letters marked for deletion
    std::string result ;
    for( char c : str ) if(c) result += c ; // copy non-deleted letters to result

    return result ;
}

const char* delete_k_cstr( char* cstr, std::size_t k )
{ return std::strcpy( cstr, delete_k(cstr,k).c_str() ) ; }

int main()
{
    std::cout << delete_k_verbose( "pixels", 3 ) << '\n' // xls
               << delete_k( "ympixeazls", 5 ) << '\n' // yxzls
               << delete_k_bgdanghe( "xpixelsx", 4 ) << '\n' ; // xxsx

    char cstr[] = "ambcdyaa" ;
    std::cout << delete_k_cstr( cstr, 4 ) << '\n' ; // myaa
}
