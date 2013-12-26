#include <iostream>
#include <sstream>
#include <fstream>

std::istringstream currentLine ;

void foo()
{
    std::string token ;
    while( currentLine >> token ) std::cout << "    token: " << token << '\n' ;
    // the stream currentLine is in a failed state at this point
    std::cout << '\n' ;
}

int main()
{
    std::ifstream file(__FILE__) ;

    std::string line ;
    int cnt = 0 ;
    while( std::getline( file, line ) )
    {
        std::cout << "line " << ++cnt << "\n----------\n" ;
        currentLine.clear() ; // *** important *** clear the failed state
        currentLine.str(line) ; // reset the buffer to the line just read
        foo() ;
    }
}
