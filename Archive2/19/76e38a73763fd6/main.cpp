#include <iostream>
#include <fstream>
#include <string>

int line_count( std::istream& stm )
{
   int n = 0 ;
   std::string line ;
   while( std::getline( stm, line ) ) ++n ;
   return n ;
}

int word_count( std::istream& stm )
{
   int n = 0 ;
   std::string word ;
   while( stm >> word ) ++n ;
   return n ;
}

int main( int argc, char *argv[] )
{
    if( argc != 2 ) std::cerr << "usage: " << argv[0] << " <text file name>\n" ;
    
    else
    {
        std::ifstream file( argv[1] ) ;
        
        if( file.is_open() )
        {
            std::cout << "number of lines: " << line_count(file) << '\n' ;
            file.clear() ;
            file.seekg(0) ;
            std::cout << "number of words: " << word_count(file) << '\n' ;
        }
        
        else
        {
            std::cerr << "cout not open input file '" << argv[1] << "'\n" ;
            return 1 ;
        }
    }
}
