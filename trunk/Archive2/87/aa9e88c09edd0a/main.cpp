#include <iostream>
#include <fstream>
#include <cstdlib>

bool copy_stream( std::istream& in, std::ostream& out ) 
{ 
    char c ;
    return out << in.rdbuf() && in.get(c).eof() && out ; 
}

bool copy_file( const std::string& input_file_name, const std::string& output_file_name )
{
    if( input_file_name == output_file_name ) return true ;

    std::ifstream in( input_file_name, std::ios::binary ) ;
    std::ofstream out( output_file_name, std::ios::binary ) ;
    return copy_stream( in, out ) ;
}

int main ()
{
    if( copy_file( __FILE__, "/tmp/copy_of_this_file" ) )
        std::system( "/bin/cat -n /tmp/copy_of_this_file" ) ;
}
