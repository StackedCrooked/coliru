#include <iostream>
#include <string>
#include <fstream>

bool copy_stream( std::istream& in, std::ostream& out )
{ return out << in.rdbuf() && out ; }

bool copy_binary_file( std::string srce_file_name, std::string dest_file_name )
{
    std::ifstream fin( srce_file_name, std::ios::binary ) ;
    std::ofstream fout(dest_file_name, std::ios::binary ) ;
    return copy_stream( fin, fout ) ;
}

bool copy_text_file( std::string srce_file_name, std::string dest_file_name )
{ return bool( std::ofstream(dest_file_name) << std::ifstream(srce_file_name).rdbuf() ) ; } 

int main()
{
    copy_text_file( __FILE__, "copy.of.main.cpp" ) ;
}