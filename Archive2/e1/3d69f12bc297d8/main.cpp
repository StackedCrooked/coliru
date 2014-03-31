#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <cstdlib>

std::string read_binary( const std::string& file_name )
{
     std::ifstream file( file_name, std::ios_base::binary ) ;

     using iterator = std::istreambuf_iterator<char> ;
     return { iterator(file), iterator() } ;
}

int main()
{
    for( std::string fname : { "/bin/grep", "/usr/bin/python", "/usr/bin/nm", "/usr/local/bin/clang++" } )
    {
        std::system( ( "wc -c " + fname ).c_str() ) ;
        std::string contents = read_binary(fname) ;
        std::cout << fname << ": " << contents.size() << " bytes were read\n\n" << std::flush ;
    }
}
