#include <iostream>
#include <fstream>
#include <string>

void foo( const std::string& path_to_file )
{
   std::ifstream file(path_to_file) ;
   std::streamoff cnt = 0 ;
   char ch ;
   while( file.get(ch) ) if( ch == '\n' ) ++cnt ;
   std::cout << "*** from foo: " << cnt << " newlines ***\n" ;
}

int main()
{
    std::string path_to_file = __FILE__ ;
    std::ifstream file(path_to_file) ;
    std::string line ;

    for( int i = 0 ; i < 10 && std::getline(file,line) ; ++i )
        std::cout << line << '\n' ;

    std::cout << "\n-----------------------------\n" ;
    foo(path_to_file) ;
    std::cout << "-----------------------------\n" ;

    while( std::getline(file,line) ) std::cout << line << '\n' ;
}
