#include <iostream>
#include <fstream>
using namespace std;

int main( int argc, char* argv[] ) 
{
    if( argc == 2 )
    {
        std::clog << "trying to open the file '" << argv[1] << "'\n" ;
        std::ifstream file( argv[1] ) ;
        if(file)
        {
            std::clog << "success!\n" ;
            std::cout << "the file contains\n--------------------\n\n" << file.rdbuf() ;
            
        }
        else std::cerr << "failed to open file for input\n" ;
    }
    else std::cerr << "usage: " << argv[0] << "  <path to the file> \n" ;
}
