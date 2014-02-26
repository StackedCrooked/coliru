#include <iostream>
#include <cstdlib>
#include <fstream>

int main()
{
    const std::string temp_file_path = "/tmp/temp.txt" ;
    const std::string cmd = "clang++ --version" ;
    
    const std::string cmd_with_stdout_to_file = cmd + " > " + temp_file_path ;  
    int status = std::system( cmd_with_stdout_to_file.c_str() ) ;

    if( status == 0 ) std::cout << std::ifstream(temp_file_path).rdbuf() ;
}
