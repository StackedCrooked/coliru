#include <iostream>
#include <fstream>
#include <string>

int main()
{
    const char* const path = "example.txt" ;
    {
        // create a test file containing two lines
        std::ofstream(path) << "Die schärfsten Kritiker der Elche\n"
                               "waren früher selber welche\n" ;
    }

    {
        // read (whitespace delimited) token by token
        std::ifstream file(path) ;
        std::string token ;

        // http://www.cplusplus.com/reference/string/string/operator%3E%3E/
        while( file >> token ) std::cout << token << '\n' ;
    }

    std::cout << "-----------------\n" ;

    {
        // read line  by line
        std::ifstream file(path) ;
        std::string line ;

        // http://www.cplusplus.com/reference/string/string/getline/
        while( std::getline( file, line ) ) std::cout << line << '\n' ;
    }
}
