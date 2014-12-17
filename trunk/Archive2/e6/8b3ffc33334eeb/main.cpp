#include <iostream>
#include <fstream>
#include <string>
#include <limits>

std::istream& goto_line( std::istream& file, unsigned int num ){

    file.clear() ; // clear failed/eof state (if any)
    file.seekg(0) ; // seek to the beginning

    for( unsigned int i = 1; i < num ; ++i )	{
        file.ignore( std::numeric_limits<std::streamsize>::max(),'\n' );
	}

	return file;
}

std::istream& get_line( std::istream& stm, std::string& line, unsigned int n ) {

    goto_line( stm, n ) ;
    return std::getline( stm, line ) ;
}

int main() {

    std::ifstream file(__FILE__) ;

    for( unsigned int n : { 4, 6, 200, 1, 4, 34, 35, 12, 6, 28 } ) {

        std::string line ;
        if( get_line( file, line, n ) ) std::cout << n << ". " << line << '\n' ;
        else std::cout << "*** error: there is no line# " << n << '\n' ;
    }
}
