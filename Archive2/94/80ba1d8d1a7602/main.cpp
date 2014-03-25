#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    const std::string word = "<string>" ;
    const char* const file_name = __FILE__ ; // "new.txt"

    std::ifstream file( file_name ) ;

    int line_number = 1 ;
    std::string line ;

    // http://www.cplusplus.com/reference/string/string/getline/
    while( std::getline( file, line ) ) // for each line in the file
    {
        // check if the word exists in the line
        // many ways to do this; the simplest is perhaps to use a string stream
        // http://www.artima.com/cppsource/streamstrings3.html
        std::istringstream stm(line) ;
        std::string test_word ;
        while( stm >> test_word ) // for each word in the line
        {
            if( test_word == word )
            {
                std::cout << "found it in line " << line_number << "\n\t"
                           << line << '\n' ;
                break ;
            }
        }

        ++line_number ;
    }

    // test case: <string> (this line should be printed just once) <string>
}
