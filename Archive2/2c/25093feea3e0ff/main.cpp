#include <iostream>
#include <string>

int main()
{
    std::string str ; // empty string
    std::cout << std::boolalpha << str.empty() << '\n' // true
              << str.size() << '\n' // 0
              << int( str[0] ) << '\n' ; // 0 (the null character after the last character has a value of zero)

    try { std::cout << str.at(0) << '\n' ; }
    catch( const std::exception& e ) { std::cerr << "out of range accesss: " << e.what() << '\n' ; }
}
