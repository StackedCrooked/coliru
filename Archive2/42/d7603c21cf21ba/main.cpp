#include <iostream>
#include <fstream>
#include <cctype>

int main ()
{
    const char* const input_file_name = __FILE__ ; // "whatever.txt"
    const char* const output_file_name = "out.txt" ;

    // opem the files
    std::ifstream input_file(input_file_name) ;
    std::ofstream output_file(output_file_name) ;

    char c ;
    while( input_file.get(c) ) // for each character (including white space) in input
    {
        const char modified = std::toupper(c) ; // some code to change the text
        output_file.put(modified) ; // write the modified character to output
    }
}
