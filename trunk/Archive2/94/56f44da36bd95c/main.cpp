#include <iostream>
#include <fstream>
#include <string>

// first line is line number 1
std::string get_line( std::istream& input_stream, int line_number )
{
    std::string line ;
    
    // read and discard lines till we reach the required line
    for( int i = 0 ; i < line_number ; ++i ) std::getline( input_stream, line ) ;
    
    // if the stram is in a good state, we have read the line successfully, return it
    // otherwise, there is an error (eg. the file does not contain that many lines)
    return input_stream ? line : "" ; 
}

int main()
{
    const std::string file_name = __FILE__ ; // "D:/EGR 125/HW 6/06HW Problem 8.4 Number 3"
    std::ifstream file(file_name) ;

    int line_number = 6 ;
    std::cout << "line " << line_number << ": " << get_line( file, line_number ) << '\n' ;
}
