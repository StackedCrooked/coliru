#include <string>
#include <iostream>
#include <fstream>

    int main()
    {
        std::ifstream file( "data.txt" ) ;
        std::string search_str = "Man" ;
        std::string line ;
        int line_number = 0 ;
        bool gotMatch = false;
        while( std::getline( file, line ) )
        {
            ++line_number;

            if (gotMatch || line.find(search_str) != std::string::npos )
            {
                std::cout << "line " << line_number << ": " << line << '\n' ;
                gotMatch = !gotMatch;
            }
        }

        return (0);
    }