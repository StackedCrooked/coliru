#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

int to_integer( std::string trimmed_str ) // decimal, hexadecimal or octal
{
    std::size_t pos = 0 ;
    // http://en.cppreference.com/w/cpp/string/basic_string/stol
    const int value = std::stoll( trimmed_str, std::addressof(pos), 0 ) ; // base == 0 => decimal, hexadecimal or octal

    if( pos != trimmed_str.size() ) throw std::domain_error( "entire string was not parsed" );
    return value  ;
}

double to_double( std::string trimmed_str ) // decimal, binary, infinity or NaN
{
    std::size_t pos = 0 ;
    // http://en.cppreference.com/w/cpp/string/basic_string/stof
    const double value = std::stod( trimmed_str, std::addressof(pos) ) ; // base == 0 => decimal, hexadecimal or octal

    if( pos != trimmed_str.size() ) throw std::domain_error( "entire string was not parsed" );
    return value  ;
}

int main()
{
    for( std::string str : { "-12345", "0xabcde", "03562", "+23.45", "-0X234P-5", "+INFINITY", "NAN", "abcd", "-1245y", "0xabkde" } )
    {
        std::cout << '\n' << str << " => " ;

        // try integer
        try { int v = to_integer(str) ; std::cout << v << " (integer)\n" ; }

        catch(...)
        {
            // not integer, try double
            try { double v = to_double(str) ; std::cout << v << " (double)\n" ; }

            // not double
            catch(...) { std::cout << str << " (string)\n" ; }
        }
    }
}
