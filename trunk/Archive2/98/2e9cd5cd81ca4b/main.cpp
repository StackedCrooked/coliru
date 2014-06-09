#include <iostream>
#include <cctype>

int main()
{
    char ch ;
    
    // get() - unformatted input (does not skip leading whitespace)
    // http://www.cplusplus.com/reference/istream/istream/get/
    // std::isspace() - http://www.cplusplus.com/reference/cctype/isspace/ 
    while( std::cin.get(ch) && !std::isspace(ch) ) std::cout << ch << ' ' << int(ch) << '\n' ;
    
    // or for formatted input with >>
    std::cin >> std::noskipws ; // http://www.cplusplus.com/reference/ios/noskipws/
    while( std::cin >> ch && !std::isspace(ch) ) std::cout << ch << ' ' << int(ch) << '\n' ;
}
