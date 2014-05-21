#include <iostream>
#include <fstream>
#include <cstdlib>

bool copy_stream( std::istream& in, std::ostream& out ) { return out << in.rdbuf() && out ; }

bool copy_text_file( const std::string& input_file, const std::string& output_file )
{
    if( input_file == output_file ) return true ;

    std::ifstream fin(input_file) ;
    std::ofstream fout(output_file) ;
    return copy_stream( fin, fout ) ;
}

int main ()
{
    if( copy_text_file( __FILE__, "copy_of_this_file" ) )
        std::system( "/bin/cat -n copy_of_this_file" ) ;
}
