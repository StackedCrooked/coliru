#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

int main()
{
    std::ifstream this_file(__FILE__) ;  // open this file

    std::string line ;
    int line_number = 0 ;

    // read line by line from file till eof
    // see: http://www.cplusplus.com/reference/string/string/getline/
    while( std::getline( this_file, line ) ) // for each line in the file
    {
        // check if it contains a "//"
        // this does not take care of:
        char this_is_not_a_comment[] = "// this is not // a comment" ;
        // and a few other constructs.
        // but we will ignore that nicety for the moment

        // does this line contain a "//" ?
        // see: http://www.cplusplus.com/reference/string/string/find/
        auto pos = line.find( "//" ) ;
        if( pos != std::string::npos ) // yes, it does
        {
            // make this line just the the part before the "//"
            // see: http://www.cplusplus.com/reference/string/string/substr/
            line = line.substr( 0, pos ) ;
        }

        // print out the line without comments
        std::cout << std::setw(2) << ++line_number << ". " << line << '\n' ;
    }
}
