#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct my_class
{
    my_class( int argc, char* argv[] )
    {
        std::vector<std::string> raw_args( argv, argv+argc ) ;
    
        for( std::string str : raw_args )
        {
            std::cout << "raw: " << str << "    parsed: " ;
            for( char& c : str )
                if( c == '(' || c == ')' || c == ',' || c == '-' ) c = ' ' ;
    
            std::istringstream stm(str) ;
            std::string token ;
            while( stm >> token ) std::cout << token << "   " ;
            std::cout << '\n' ;
        }
    }
};


int main( int argc, char* argv[] ) {  my_class( argc, argv ) ; }
