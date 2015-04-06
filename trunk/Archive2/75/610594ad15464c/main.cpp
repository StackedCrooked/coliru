#include <iostream>
#include <string>

int main( int argc, char* argv[] )
{
    for( int i = 0 ; i < argc ; ++i )
    {
        std::cout << i << ". '" << argv[i] << "' " ;

        try
        {
            const std::string str = argv[i] ;
            std::size_t pos ;
            // http://en.cppreference.com/w/cpp/string/basic_string/stol
            const int value =  std::stoi( str, &pos, 10 ) ; // decimal integer literal
            if( pos == str.size() ) std::cout << "integer value is " << value << '\n' ;
            else std::cout << "partial conversion to int; value: " << value << " (non-numeric character found at position " << pos << ")\n" ;
        }
        
        catch( const std::invalid_argument& ) { std::cout << "invalid characters: no conversion could be performed\n" ; }
        
        catch( const std::out_of_range& ) { std::cout << "integer value is out of the range of int\n" ; }
    }
}
