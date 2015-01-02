#include <string>
#include <cstdio>
#include <iostream>

int main()
{
    const char* hex_str = ""4D65727279 4368726973746D6173 41726F6E" ;

    std::string result_string ;
    unsigned int ch ;
    for( ; std::sscanf( hex_str, "%2x", &ch ) == 1 ; hex_str += 2 )
        result_string += ch ;

    std::cout << result_string << '\n' ;
}