#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);

std::string pipe_to_string( const char* command )
{
    FILE* file = popen( command, "r" ) ;

    if( file )
    {
        std::ostringstream stm ;

        constexpr std::size_t MAX_LINE_SZ = 1024 ;
        char line[MAX_LINE_SZ] ;

        while( fgets( line, MAX_LINE_SZ, file ) ) stm << line << '\n' ;

        pclose(file) ;
        return stm.str() ;
    }

    return "" ;
}

int main()
{
    const std::string result = pipe_to_string( "ls -la" ) ;
    std::cout << result << '\n' ;
    // ...
}
