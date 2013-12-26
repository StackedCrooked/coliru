#include <iostream>
#include <string>
#include <type_traits>
#include <sstream>
#include <complex>

namespace detail
{
    // if it is a std::string, a c-style string or a character, append directly
    void append_text( std::string& str, const std::string& v ) { str += v ; }
    void append_text( std::string& str, const char* v ) { str += v ; }
    void append_text( std::string& str, char v ) { str += v ; }
    void append_text( std::string& str, signed char v ) { str += char(v) ; }
    void append_text( std::string& str, unsigned char v ) { str += char(v) ; }

    template < typename T > struct use_std_to_string : std::false_type {};
    template <> struct use_std_to_string<short> : std::true_type {};
    template <> struct use_std_to_string<unsigned short> : std::true_type {};
    template <> struct use_std_to_string<int> : std::true_type {};
    template <> struct use_std_to_string<unsigned int> : std::true_type {};
    template <> struct use_std_to_string<long> : std::true_type {};
    template <> struct use_std_to_string<unsigned long> : std::true_type {};
    template <> struct use_std_to_string<long long> : std::true_type {};
    template <> struct use_std_to_string<unsigned long long> : std::true_type {};
    template <> struct use_std_to_string<float> : std::true_type {};
    template <> struct use_std_to_string<double> : std::true_type {};
    template <> struct use_std_to_string<long double> : std::true_type {};

    // if std::to_string() can be used, use it for stringification, append
    template< typename T >
    typename std::enable_if< use_std_to_string< typename std::decay<T>::type >::value, void >::type
    append_text( std::string& str, const T& v ) { str += std::to_string(v) ; }

    // if std::to_string() can't be used, append via a stringstream
    template< typename T >
    typename std::enable_if< !use_std_to_string< typename std::decay<T>::type >::value, void >::type
    append_text( std::string& str, const T& v )
    { std::ostringstream stm( str, std::ios::app ) ; stm << v ; str = stm.str() ; }
    
    template< typename FIRST, typename... REST >
    void append_text( std::string& str, const FIRST& first, const REST&... rest )
    {
        append_text( str, first ) ;
        append_text( str, rest...) ;
    }
}

struct qbFont
{
    template < typename... ARGS > void set_text( const ARGS&... args )
    {
        std::string tempText ;
        detail::append_text( tempText, args... ) ;
        std::cout << "qbFont::set_text::tempText is: '" << tempText << "'\n" ;
        /*
            go through every symbol in this string
            and pick a texture of a letter/number and add to a quad
        */
    }
};

int main()
{
    const int score = 762 ;
    const std::complex<double> cmplx( 1.2, 3.4 ) ;

    qbFont font ;
    font.set_text( "Score: " , score , " Points!" ) ;
    font.set_text( "test: " , cmplx , " (no std::to_string)", " done", '!' ) ;
}
