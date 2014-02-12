



              #include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int main()
{
    std::ifstream file( __FILE__ ) ;

    char c ;
    if( file >> c ) file.putback(c) ; // read and put back the first non-ws character

    std::stringstream stm ;
    stm << file.rdbuf() ;

    std::string memblock = stm.str() ;
    std::cout << memblock ;
}