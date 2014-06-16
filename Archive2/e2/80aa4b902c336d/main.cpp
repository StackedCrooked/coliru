#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() 
{
    struct stat buf ;
    
    for( const std::string path : { "./test_dir", "./main.cpp", "./../../usr/local/include", "bad_path" } )
    {
        std::cout << '\'' << path << "' : " ;
        if( stat( path.c_str(), &buf ) == 0 )
        {
            const mode_t mode = buf.st_mode ;
            
            if( S_ISREG(mode) ) std::cout << "regular file\n" ;
            else if( S_ISDIR(mode) ) std::cout << "directory\n" ;
            // etc.
        }
        else std::cout << "*** stat error ***\n" ;
    }
}
