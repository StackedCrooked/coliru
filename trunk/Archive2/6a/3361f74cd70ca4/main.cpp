#include <iostream>
#include <string>
#include <cctype>

int char_to_int( char c ) // convert character '0', '1', ... '9' to int
{
    // http://en.cppreference.com/w/cpp/string/byte/isdigit
    if( !std::isdigit(c) ) return 0 ; // character is not a decimal digit

    // characters '0', '1', ... '9' have consecutive values
    // '4' - '0' == 0    '7' - '0' == 7 etc.
    return c - '0' ;
}

static int depth = 0 ;

// invariant: string contains only decimal digits with no leading sign
// assumes that there would not be an integer overflow
int string_to_int( std::string str )
{
    for( int i = 0 ; i < depth ; ++i ) std::cout << "  " ;
    ++depth ;
    std::cout << "str: " << str ;

    if( str.empty() ) return 0 ;

    if( str.size() == 1 )
    {
        const int value = char_to_int( str[0] ) ;
        std::cout << "  => return " << value << '\n' ;
        --depth ;
        return value ;
    }

    // http://en.cppreference.com/w/cpp/string/basic_string/back
    const int last_digit = char_to_int( str.back() ) ;
    std::cout << "  last digit: " << last_digit  << ' ' ;

    // http://en.cppreference.com/w/cpp/string/basic_string/pop_back
    str.pop_back() ; // digits except the last digit
    std::cout << "  remaining: " << str << '\n' ;

    const int value_of_remaining_digits = string_to_int(str) ;
    const int value = value_of_remaining_digits * 10 + last_digit ;

    --depth ;
    for( int i = 0 ; i < depth ; ++i ) std::cout << "  " ;
    std::cout << value_of_remaining_digits << " * 10 + " << last_digit
              << " == " << value << "  => return " << value << '\n' ;

    return value ;
}

int main()
{
    for( std::string str : { "1234", "567", "987654" } )
    {
        depth = 0 ;
        std::cout << str << '\n' ;
        std::cout << string_to_int(str) << "\n------------------\n\n" ;
    }
}
