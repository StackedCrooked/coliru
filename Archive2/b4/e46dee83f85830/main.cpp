#include <iostream>
#include <string>
#include <regex>

int main()
{
    const std::string bar = "\\|" ; // escaped bar
    const std::string space = "\\s+" ; // one or more spaces (escaped white space)
    const std::string cap = "\\^" ;
    const std::string plus = "\\+" ;

    const std::regex pattern_one( bar + space + bar + bar + space + bar + bar ) ;
    const std::regex pattern_two( bar + cap + space + plus + space + bar + bar + space + plus + space + bar + bar ) ;

    const std::string string_one = "|          ||          ||" ;
    const std::string string_two = "|^  +      ||     +    ||" ;

    if( std::regex_match( string_one, pattern_one ) ) std::cout << "string_one matched pattern_one\n" ;
    if( std::regex_match( string_one, pattern_two ) ) std::cout << "string_one matched pattern_two\n" ;

    if( std::regex_match( string_two, pattern_one ) ) std::cout << "string_two matched pattern_one\n" ;
    if( std::regex_match( string_two, pattern_two ) ) std::cout << "string_two matched pattern_two\n" ;
}
