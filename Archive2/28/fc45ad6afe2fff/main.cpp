#include <iostream>
#include <sstream>
#include <string>

int main()
{
    constexpr char COMMA = ',' ;

    std::istringstream file(
                                "      ORG         100\n"
                                "      LOAD        X\n"
                                "      ADD         Y\n"
                                "      STORE       Z\n"
                                "      HALT\n"
                                "X,    DEC         49\n"
                                "Y,    DEC         -80\n"
                                "Z,    HEX         0000\n"
                            ) ;

    std::string line ;
    while( std::getline( file, line ) )
    {
        std::cout << line  << "   (column one is: '" ;

        std::string col_one ;

        if( line.find( COMMA ) != std::string::npos ) // if a comma is found
        {
            std::istringstream stm(line) ; // put the line into a string stream
            // read everything starting from the first non-whitespace character
            // upto, but not including the comma
            std::getline( stm >> std::skipws, col_one, COMMA ) ;
        }

        std::cout << col_one << "')\n" ;
    }
}
