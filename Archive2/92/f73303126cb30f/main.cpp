#include <iostream>
#include <string>
#include <fstream>

bool is_an_integer( std::string trimmed_str ) // decimal, hexadecimal or octal
{
    try
    {
        std::size_t pos = 0 ;
        // http://en.cppreference.com/w/cpp/string/basic_string/stol
        std::stoll( trimmed_str, std::addressof(pos), 0 ) ; // base == 0 => decimal, hexadecimal or octal
        return pos == trimmed_str.size() ; // the whole string was parsed
    }
    catch(...) {}

    return false ;
}

bool is_a_real_number( std::string trimmed_str ) // decimal, binary, infinity or NaN
{
    try
    {
        std::size_t pos = 0 ;
        // http://en.cppreference.com/w/cpp/string/basic_string/stof
        std::stold( trimmed_str, std::addressof(pos) ) ;
        return pos == trimmed_str.size() ; // the whole string was parsed
    }
    catch(...) {}

    return false ;
}

bool is_a_number( std::string str )
{ return is_an_integer(str) || is_a_real_number(str) ; }

// -12345 0xabcde 03562 +23.45 -0X234P5 +INFINITY NAN 

int main()
{
    int n_integers = 0 ;
    int n_real_numbers = 0 ;
    int n_words = 0 ;
    
    const char* const path = __FILE__ ; // "C:/Users/User/Desktop/programming110/random.txt"
    std::ifstream file(path) ;
    std::string str ;
    while( file >> str )
    {
        if( is_a_real_number(str) )
        {
            ++n_real_numbers ; // integers are real numbers
            if( is_an_integer(str) ) ++n_integers ; 
        }
        
        else ++n_words ;
    }

    // print counts
    std::cout << "integers: " << n_integers << "  real numbers: " << n_real_numbers << "  other: " << n_words << '\n' ;
}
